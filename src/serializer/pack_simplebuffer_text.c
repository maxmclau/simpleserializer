/**
 *  Copyright (c) 2010  Yukio Obuchi
 * 
 *   Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation files
 *  (the "Software"), to deal in the Software without restriction,
 *  including without limitation the rights to use, copy, modify, merge,
 *  publish, distribute, sublicense, and/or sell copies of the Software,
 *  and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 * 
 *   The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 * 
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 *  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 *  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <stdio.h>
#include <string.h>

#include <simplebuffer.h>
#include <unpack.h>
#include <pack_simplebuffer.h>
#include <pack_simplebuffer_text.h>

#include "text_serializer.h"

typedef enum 
{
    PACK_STATE_NORMAL,
    PACK_STATE_STRING,
    PACK_STATE_STRING_ESCAPE,
    PACK_STATE_RAW,
    END_OF_PACK_STATE
} pack_state_t;

static const char *braceopen = "[{(@";
static const char *braceclose = "]}(@";
static const char *splitter = ", \t";

static bool character_is_splitter( char c )
{
    return strchr( splitter, c ) != NULL;
}

static unsigned int get_hex_value( simplebuffer *string )
{
    size_t i = 0;
    uint32_t value = 0;

    for( i = 2; i < string->size-1; i++ )
    {
        char c = string->data[i];
        value <<= 4;
        if( c >= '0' && c <= '9' )      { value |= c - '0';       }
        else if( c >= 'A' && c <= 'F' ) { value |= c - 'A' + 0xa; }
        else if( c >= 'a' && c <= 'f' ) { value |= c - 'a' + 0xa; }
    }
    return value;
}

static uint32_t get_int_value( simplebuffer *string )
{
    size_t i = 0;
    int32_t value = 0;

    for( ; i < string->size-1; i++ )
    {
        char c = string->data[i];
        if( c >= '0' && c <= '9' )
        {
            value = (value * 10) + (c - '0');
        }
    }

    if( string->data[0] == '-' )
    {
        value = value * -1;
    }

    return value;
}

static uint32_t get_uint_value( simplebuffer *string )
{
    size_t i = 0;
    uint32_t value = 0;

    for( i = 0; i < string->size-1; i++ )
    {
        char c = string->data[i];
        if( c >= '0' && c <= '9' )
        {
            value = (value * 10) + (c - '0');
        }
        else
        {
            break;
        }
    }
    return value;
}

static double get_double_value( simplebuffer *string )
{
    size_t i = 0, j = 0;
    double value = 0;
    bool is_afterdecimal = false;
    size_t afterdecimalcount = 0;

    for( i = 0; i < string->size-1; i++ )
    {
        char c = string->data[i];
        if( c >= '0' && c <= '9' )
        {
            if( is_afterdecimal )
            {
                double tmp = (double)(c - '0');
                for( j = 0; j < afterdecimalcount; j++ )
                {
                    tmp = tmp / 10;
                }
                value = value + tmp;

                afterdecimalcount += 1;
            }
            else
            {
                value = (value * 10) + (c - '0');
            }
        }
        else if( c == '.' )
        {
            is_afterdecimal = true;
            afterdecimalcount = 1;
        }
    }

    if( string->data[0] == '-' )
    {
        value = value * -1;
    }

    return value;
}

static bool string_is_int( simplebuffer *string )
{
    size_t i = 0;
    if( string->size > 2 &&
        (string->data)[string->size - 2] == 'd' )
    {
        if( (string->data)[0] == '-' ||
            (string->data)[0] == '+' )
        {
            i = 1;
        }
        for( ; i < string->size-2; i++ )
        {
            char c = (string->data)[i];
            if( !(c >= '0' && c <= '9') )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool string_is_unsigned_int( simplebuffer *string )
{
    size_t i = 0;
    if( string->size > 2 &&
        (string->data)[string->size - 2] == 'u' )
    {
        if( (string->data)[0] == '+' )
        {
            i = 1;
        }
        for( ; i < string->size-2; i++ )
        {
            char c = (string->data)[i];
            if( !(c >= '0' && c <= '9') )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool string_is_float( simplebuffer *string )
{
    size_t i = 0;
    size_t num_of_points = 0;

    if( string->size > 2 &&
        (string->data)[string->size - 2] == 'f' )
    {
        if( (string->data)[0] == '-' ||
            (string->data)[0] == '+' )
        {
            i = 1;
        }
        for( ; i < string->size-2; i++ )
        {
            char c = (string->data)[i];
            if( c == '.' )
            {
                num_of_points += 1;
            }
            else if( !(c >= '0' && c <= '9' ) )
            {
                return false;
            }
        }
        if( num_of_points == 0 || num_of_points == 1 )
        {
            return true;
        }
    }
    return false;
}

static bool string_is_double( simplebuffer *string )
{
    size_t i = 0;
    size_t num_of_points = 0;

    if( string->size > 3 &&
        (string->data)[string->size - 3] == 'l' &&
        (string->data)[string->size - 2] == 'f' )
    {
        if( (string->data)[0] == '-' ||
            (string->data)[0] == '+' )
        {
            i = 1;
        }
        for( ; i < string->size-3; i++ )
        {
            char c = (string->data)[i];
            if( c == '.' )
            {
                num_of_points += 1;
            }
            else if( !(c >= '0' && c <= '9' ) )
            {
                return false;
            }
        }
        if( num_of_points == 0 || num_of_points == 1 )
        {
            return true;
        }
    }
    return false;
}

static bool string_is_hex( simplebuffer *string )
{
    size_t i = 0;

    if( string->size > 3 &&
        (string->data)[0] == '0' &&
        (string->data)[1] == 'x' )
    {
        i = 2;
        for( ; i < string->size - 1; i++ )
        {
            char c = (string->data)[i];
            if( !( (c >= '0' && c <= '9') ||
                   (c >= 'A' && c <= 'F') ||
                   (c >= 'a' && c <= 'f') ))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static unpack_info_t text_to_value( simplebuffer *string )
{
    unpack_info_t info = { 0 };
    if( string->size > 0 )
    {
        if( string_is_hex( string ) )
        {
            info.type = UNPACK_TYPE_UINT;
            info.value.uint_value = get_hex_value( string );
        }
        else if( string_is_double( string ) )
        {
            info.type = UNPACK_TYPE_DOUBLE;
            info.value.double_value = get_double_value( string );
        }
        else if( string_is_float( string ) )
        {
            info.type = UNPACK_TYPE_FLOAT;
            info.value.float_value = (float)get_double_value( string );
        }
        else if( string_is_int( string ) )
        {
            info.type = UNPACK_TYPE_INT;
            info.value.int_value = get_int_value( string );
        }
        else if( string_is_unsigned_int( string ) )
        {
            info.type = UNPACK_TYPE_UINT;
            info.value.uint_value = get_uint_value( string );
        }
        else
        {
            size_t i = 0;
            size_t num_of_point = 0;
            bool is_numeric = true;
            if( string->data[0] == '-' ||
                string->data[0] == '+' )
            {
                i = 1;
            }
            
            for( ; i < string->size; i++ )
            {
                char c = string->data[i];
                if( c == '.' )
                {
                    num_of_point += 1;
                }
                else if( c != 0 && ( c < '0' || c > '9' ))
                {
                    is_numeric = false;
                }
            }

            if( is_numeric )          // その他の場合はintとみなす
            {
                if( num_of_point == 1 ) // 「.」が含まれていればDoubleとみなす
                {
                    info.type = UNPACK_TYPE_DOUBLE;
                    info.value.double_value = get_double_value( string );
                }
                else
                {
                    info.type = UNPACK_TYPE_INT;
                    info.value.int_value = get_int_value( string );
                }
            }
            else
            {
                info.type = UNPACK_TYPE_RAW;
            }
            
        }
    }
    return info;
}

static void check_token( simplebuffer* serialized,simplebuffer* token,struct nest_info_t *nest,size_t nestlevel )
{
    if( token->size != 0 )
    {
        simplebuffer_write( token, (uint8_t*)"", 1 );

        nest[nestlevel].num_of_element += 1;
        if( nestlevel == 0 )
        {
            if( nest[nestlevel].type == T_STRING )
            {
                pack_simplebuffer_raw(serialized, token->data, token->size);
            }
            else if( nest[nestlevel].type == T_RAW )
            {
                unpack_info_t v = text_to_value( token );
                char c = (char)(v.value.uint_value & 0xff);
                simplebuffer_write(serialized, (uint8_t*)&c, 1);
            }
            else
            {
                unpack_info_t v = text_to_value( token );
                if( v.type == UNPACK_TYPE_INT )
                {
                    pack_simplebuffer_int( serialized,  v.value.int_value );
                }
                else if( v.type == UNPACK_TYPE_UINT )
                {
                    pack_simplebuffer_uint( serialized,  v.value.uint_value );
                }
                else if( v.type == UNPACK_TYPE_FLOAT )
                {
                    pack_simplebuffer_float( serialized,  v.value.float_value );
                }
                else if( v.type == UNPACK_TYPE_DOUBLE )
                {
                    pack_simplebuffer_double( serialized,  v.value.double_value );
                }
                else if( v.type == UNPACK_TYPE_RAW )
                {
                    pack_simplebuffer_raw(serialized, token->data, token->size);
                }
            }
        }

        simplebuffer_destroy( token );
    }
}

static void pack_simplebuffer_text_sub( simplebuffer* serialized,
                                        char *text,
                                        size_t start,
                                        size_t end,
                                        array_type_t type,
                                        pack_state_t initial_state )
{
    size_t i;
    pack_state_t state = initial_state;
    pack_state_t next_state = initial_state;
    simplebuffer token = {0};

    struct nest_info_t nest[ (int)MAX_NEST_LEVEL ] = { {(array_type_t)0} };
    size_t nestlevel = 0;
    nest[nestlevel].type = type;
    
    char recent_char = 0;
    for( i = start; i < end; i++ )
    {
        char c = *(text + i);
        if( state == PACK_STATE_NORMAL )
        {
            if( character_is_splitter( c ) )
            {
                check_token(serialized, &token, nest, nestlevel);
            }
            else if( c == braceopen[0] )
            {
                check_token(serialized, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_ARRAY;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
            }
            else if( c == braceopen[1] )
            {
                check_token(serialized, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_STRUCT;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
            }
            else if( c == braceclose[0] )
            {
                check_token(serialized, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    pack_simplebuffer_array_header( serialized, (int)nest[nestlevel].num_of_element);
                    pack_simplebuffer_text_sub( serialized, text, nest[nestlevel].offset+1, i, T_ARRAY, state );
                }
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
            }
            else if( c == braceclose[1] )
            {
                check_token(serialized, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    pack_simplebuffer_nil(serialized);
                    pack_simplebuffer_array_header(serialized, (int)nest[nestlevel].num_of_element);
                    pack_simplebuffer_text_sub( serialized, text, nest[nestlevel].offset+1, i, T_STRUCT, state );
                }
                
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
            }
            else if( c == '"' )
            {
                check_token(serialized, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_STRING;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
                next_state = PACK_STATE_STRING;
            }
            else if( c == '<' )
            {
                check_token(serialized, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_RAW;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
                next_state = PACK_STATE_RAW;
            }
            else
            {
                simplebuffer_write( &token, (uint8_t*)&c, 1 );
            }
        }
        else if( state == PACK_STATE_STRING )
        {
            if( c == '\\' )
            {
                next_state = PACK_STATE_STRING_ESCAPE;
            }
            else if( c == '"' )
            {
                check_token(serialized, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    pack_simplebuffer_text_sub( serialized, text, nest[nestlevel].offset+1, i, T_STRING, state );
                }
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
                next_state = PACK_STATE_NORMAL;
            }
            else
            {
                simplebuffer_write( &token, (uint8_t*)&c, 1 );
            }
        }
        else if( state == PACK_STATE_STRING_ESCAPE )
        {
            simplebuffer_write( &token, (uint8_t*)&c, 1 );
            next_state = PACK_STATE_STRING;
        }
        else if( state == PACK_STATE_RAW )
        {
            if( character_is_splitter( c ) )
            {
                check_token(serialized, &token, nest, nestlevel);
            }
            else if( c == '>' )
            {
                check_token(serialized, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    pack_simplebuffer_raw_header(serialized, (int)nest[nestlevel].num_of_element);
                    pack_simplebuffer_text_sub( serialized, text, nest[nestlevel].offset+1, i, T_RAW, state );
                }
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
                next_state = PACK_STATE_NORMAL;
            }
            else
            {
                simplebuffer_write( &token, (uint8_t*)&c, 1 );
            }
        }
        state = next_state;
        recent_char = c;
    }
    check_token(serialized, &token, nest, nestlevel);
}

simplebuffer pack_simplebuffer_text( char *text )
{
    simplebuffer serialized;
    simplebuffer_init( &serialized, NULL, 0 );
    pack_simplebuffer_text_sub( &serialized, text, 0, strlen( text ), T_NORMAL, PACK_STATE_NORMAL );

    return serialized;
}
