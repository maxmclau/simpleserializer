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
#include <unpack_simplebuffer_text.h>

#include "text_serializer.h"

simplebuffer unpack_simplebuffer_text( simplebuffer serialized )
{
    simplebuffer text;
    uint8_t tmpbuf[ MAX_PRINT_VALUE_LENGTH ];
    struct nest_info_t nest[ MAX_NEST_LEVEL ];
    size_t tmpsize;
    
    size_t nestlevel = 0;
    int offset = 0;
    array_type_t next_type = T_NONE;

    simplebuffer_init( &text, NULL, 0 );
    nest[nestlevel].type = T_NONE;
    nest[nestlevel].num_of_element = -1;
    nest[nestlevel].offset = 0;
    while( offset < serialized.size )
    {
        bool is_nil = false;
        bool is_array_start = false;
        unpack_info_t info;
        offset += unpack( &info, (uint8_t*)(serialized.data + offset) );
        switch( info.type )
        {
            case UNPACK_TYPE_NIL:
                next_type = T_STRUCT;
                is_nil = true;
                break;
            case UNPACK_TYPE_BOOL:
                if( info.value.bool_value )
                {
                    simplebuffer_write( &text, (uint8_t*)"true", 4 );
                }
                else
                {
                    simplebuffer_write( &text, (uint8_t*)"false", 5 );
                }
                break;
                
            case UNPACK_TYPE_INT:
                tmpsize = sprintf( (char *)tmpbuf, "%dd",
                                   (int)(info.value.int_value) );
                simplebuffer_write( &text, tmpbuf, tmpsize );
                break;
                
            case UNPACK_TYPE_UINT:
                tmpsize = sprintf( (char *)tmpbuf, "%uu",
                                   (unsigned int)(info.value.uint_value) );
                simplebuffer_write( &text, tmpbuf, tmpsize );
                break;
                
            case UNPACK_TYPE_FLOAT:
                tmpsize = sprintf( (char *)tmpbuf, "%ff", info.value.float_value );
                simplebuffer_write( &text, tmpbuf, tmpsize );
                break;
                
#ifdef SUPPORT_64BIT_VALUE
            case UNPACK_TYPE_DOUBLE:
                tmpsize = sprintf( (char *)tmpbuf, "%lflf", info.value.double_value );
                simplebuffer_write( &text, tmpbuf, tmpsize );
                break;
#endif
                
            case UNPACK_TYPE_RAW:
            {
                bool is_printable = true;
                size_t i = 0;
                for( i = 0; i < info.value.raw_value.size-1; i ++)
                {
                    if( *(info.value.raw_value.data + i ) < ' ' ||
                        *(info.value.raw_value.data + i ) == '"' )
                    {
                        is_printable = false;
                    }
                }
                if( *(info.value.raw_value.data + i) != 0 )
                {
                    is_printable = false;
                }
                
                
                if( is_printable )
                {
                    tmpsize = sprintf( (char *)tmpbuf, "\"%s\"", info.value.raw_value.data );
                    simplebuffer_write( &text, tmpbuf, tmpsize );
                }
                else
                {
                    size_t i = 0;
                    tmpsize = sprintf( (char *)tmpbuf, "<" );
                    simplebuffer_write( &text, tmpbuf, tmpsize );
                    for( i = 0; i < info.value.raw_value.size; i ++)
                    {
                        tmpsize = sprintf( (char *)tmpbuf, "0x%02X",
                                           *(info.value.raw_value.data + i) & 0xff);
                        simplebuffer_write( &text, tmpbuf, tmpsize );
                        if ( i < info.value.raw_value.size-1 )
                        {
                            tmpsize = sprintf( (char *)tmpbuf, ", " );
                            simplebuffer_write( &text, tmpbuf, tmpsize );
                        }
                        

                    }
                    tmpsize = sprintf( (char *)tmpbuf, ">" );
                    simplebuffer_write( &text, tmpbuf, tmpsize );
                }
            } break;
                
            case UNPACK_TYPE_ARRAY:
                is_array_start = true;
                if( next_type == T_NONE )
                {
                    next_type = T_ARRAY;
                }
                switch( next_type )
                {
                    case T_ARRAY: tmpsize = sprintf( (char *)tmpbuf, "[" ); break;
                    case T_STRUCT:tmpsize = sprintf( (char *)tmpbuf, "{" ); break;
                    default: tmpsize = sprintf( (char *)tmpbuf, "@" ); break;
                }
                simplebuffer_write( &text, tmpbuf, tmpsize );
                nestlevel += 1;
                nest[nestlevel].type = next_type;
                nest[nestlevel].num_of_element = (int)(info.value.size_value);
                nest[nestlevel].offset = 0;
                break;
            default:
                break;
        }

        if( nestlevel > 0 && !is_nil )
        {
            while( nestlevel > 0 &&
                   nest[nestlevel].offset >= nest[nestlevel].num_of_element )
            {
                switch( nest[nestlevel].type )
                {
                    case T_STRUCT:tmpsize = sprintf( (char *)tmpbuf, "}" ); break;
                    case T_ARRAY: tmpsize = sprintf( (char *)tmpbuf, "]" ); break;
                    default: tmpsize = sprintf( (char *)tmpbuf, "@" ); break;
                }
                simplebuffer_write( &text, tmpbuf, tmpsize );
                nestlevel -= 1;
            } 
        }

        if( offset < serialized.size && !is_array_start && !is_nil )
        {
            tmpsize = sprintf( (char *)tmpbuf, ", " );
            simplebuffer_write( &text, tmpbuf, tmpsize );
        }

        if( !is_nil )
        {
            next_type = T_NONE;
            nest[nestlevel].offset += 1;
        }

    }
    simplebuffer_write( &text, (uint8_t*)"", 1 );
    return text;
}
