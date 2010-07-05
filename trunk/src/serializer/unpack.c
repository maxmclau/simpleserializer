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

#include "defines.h"
#include "unpack.h"

#include <stdint.h>

/// Get 8bit value from buffer.
#define UNPACK_GET_8BIT_VALUE(d)  (*(d))


/// Get 16bit value from buffer.
#define UNPACK_GET_16BIT_VALUE(d)         \
    ((uint16_t)(*d) << 8) |               \
    (uint16_t)(*(d+1))

/// Get 32bit value from buffer.
#define UNPACK_GET_32BIT_VALUE(d)         \
    ((uint32_t)(*d) << 24)     |          \
    ((uint32_t)*(d+1) << 16) |            \
    ((uint32_t)*(d+2) <<  8) |            \
    (uint32_t)*(d+3)

#ifdef SUPPORT_64BIT_VALUE
/// Get 64bit value from buffer.
#define UNPACK_GET_64BIT_VALUE(d)         \
    ((uint64_t)(*d) << 56)   |            \
    ((uint64_t)*(d+1) << 48) |            \
    ((uint64_t)*(d+2) << 40) |            \
    ((uint64_t)*(d+3) << 32) |            \
    ((uint64_t)*(d+4) << 24) |            \
    ((uint64_t)*(d+5) << 16) |            \
    ((uint64_t)*(d+6) <<  8) |            \
    (uint64_t)*(d+7)
#endif

unpack_base_info_t unpack_base( uint8_t* buf )
{
    unpack_base_info_t info = {0};
    unsigned char header = (uint8_t)(UNPACK_GET_8BIT_VALUE(buf));
    buf++;

    info.type = header;
    if( header == TYPE_VALIABLE_NIL )
    {
        info.size = 1;
    }
    else if( header == TYPE_VALIABLE_FALSE )
    {
        info.size = 1;
    }
    else if( header == TYPE_VALIABLE_TRUE )
    {
        info.size = 1;
    }
    else if( header == TYPE_VALIABLE_FLOAT )
    {
        info.size = 5;
        info.value.uint32_value = (uint32_t)(UNPACK_GET_32BIT_VALUE(buf));
    }
#ifdef SUPPORT_64BIT_VALUE
    else if( header == TYPE_VALIABLE_DOUBLE )
    {
        info.size = 9;
        info.value.uint64_value = (uint64_t)(UNPACK_GET_64BIT_VALUE(buf));
    }
#endif
    else if( header == TYPE_VALIABLE_UINT8 )
    {
        info.size = 2;
        info.value.uint8_value = (uint8_t)(UNPACK_GET_8BIT_VALUE(buf));
    }
    else if( header == TYPE_VALIABLE_UINT16 )
    {
        info.size = 3;
        info.value.uint16_value = (uint16_t)(UNPACK_GET_16BIT_VALUE(buf));
    }
    else if( header == TYPE_VALIABLE_UINT32 )
    {
        info.size = 5;
        info.value.uint32_value = (uint32_t)(UNPACK_GET_32BIT_VALUE(buf));
    }
#ifdef SUPPORT_64BIT_VALUE
    else if( header == TYPE_VALIABLE_UINT64 )
    {
    }
#endif
    else if( header == TYPE_VALIABLE_INT8 )
    {
        info.size = 2;
        info.value.uint8_value = (uint8_t)(UNPACK_GET_8BIT_VALUE(buf));
    }
    else if( header == TYPE_VALIABLE_INT16 )
    {
        info.size = 3;
        info.value.uint16_value = (int16_t)(UNPACK_GET_16BIT_VALUE(buf));
    }
    else if( header == TYPE_VALIABLE_INT32 )
    {
        info.size = 5;
        info.value.uint32_value = (int32_t)(UNPACK_GET_32BIT_VALUE(buf));
    }
#if 0
    else if( header == TYPE_VALIABLE_INT64 )
    {
    }
#endif
    else if( header == TYPE_VALIABLE_RAW16 )
    {
        size_t data_size = (size_t)(UNPACK_GET_16BIT_VALUE(buf));
        info.size = 3;
        info.value.size = data_size;
    }
    else if( header == TYPE_VALIABLE_RAW32 )
    {
        size_t data_size = (size_t)(UNPACK_GET_32BIT_VALUE(buf));
        info.size = 5;
        info.value.size = data_size;
    }
#if 0
    else if( header == TYPE_VALIABLE_ARRAY16 )
    {
    }
    else if( header == TYPE_VALIABLE_ARRAY32 )
    {
    }
    else if( header == TYPE_VALIABLE_MAP16 )
    {
    }
    else if( header == TYPE_VALIABLE_MAP32 )
    {
    }
#endif
    else
    {
        if( (header & TYPE_POSITIVE_FIXNUM_MASK) ==  TYPE_POSITIVE_FIXNUM )
        {
            info.size = 1;
            info.type = TYPE_POSITIVE_FIXNUM;
            info.value.uint8_value = (uint8_t)(header);
        }
        else if( (header & TYPE_NEGATIVE_FIXNUM_MASK) ==  TYPE_NEGATIVE_FIXNUM )
        {
            info.size = 1;
            info.type = TYPE_NEGATIVE_FIXNUM;
            info.value.int8_value = (int8_t)(header);
        }
        else if( (header & TYPE_FIXROW_MASK) == TYPE_FIXROW )
        {
            info.size = 1;
            info.type = TYPE_FIXROW;
            info.value.size = (size_t)(header & ~TYPE_FIXROW_MASK);
        }
#if 0
        else if( (header & TYPE_FIXARRAY_MASK) ==  TYPE_FIXARRAY )
        {
        }
        else if( (header & TYPE_FIXMAP_MASK) ==  TYPE_FIXMAP )
        {
        }
#endif
    }
    return info;
}

int unpack( unpack_info_t *info, uint8_t* buf )
{
    unpack_base_info_t info_base = unpack_base( buf );
    int size = info_base.size;
    if( info_base.type == TYPE_VALIABLE_NIL )
    {
        info->type = UNPACK_TYPE_NIL;
    }
    else if( info_base.type == TYPE_VALIABLE_FALSE )
    {
        info->type = UNPACK_TYPE_BOOL;
        info->value.bool_value = false;
    }
    else if( info_base.type == TYPE_VALIABLE_TRUE )
    {
        info->type = UNPACK_TYPE_BOOL;
        info->value.bool_value = true;
    }
    else if( info_base.type == TYPE_POSITIVE_FIXNUM || info_base.type == TYPE_VALIABLE_UINT8 )
    {
        info->type = UNPACK_TYPE_UINT;
        info->value.uint_value = (unsigned int)info_base.value.uint8_value;
    }
    else if( info_base.type == TYPE_VALIABLE_UINT16 )
    {
        info->type = UNPACK_TYPE_UINT;
        info->value.uint_value = (unsigned int)info_base.value.uint16_value;
    }
    else if( info_base.type == TYPE_VALIABLE_UINT32 )
    {
        info->type = UNPACK_TYPE_UINT;
        info->value.uint_value = (unsigned int)info_base.value.uint32_value;
    }
    else if( info_base.type == TYPE_NEGATIVE_FIXNUM || info_base.type == TYPE_VALIABLE_INT8 )
    {
        info->type = UNPACK_TYPE_INT;
        info->value.int_value = (int)info_base.value.int8_value;
    }
    else if( info_base.type == TYPE_VALIABLE_INT16 )
    {
        info->type = UNPACK_TYPE_INT;
        info->value.int_value = (int)info_base.value.int16_value;
    }
    else if( info_base.type == TYPE_VALIABLE_INT32 )
    {
        info->type = UNPACK_TYPE_INT;
        info->value.int_value = (int)info_base.value.int32_value;
    }
    else if( info_base.type == TYPE_FIXROW ||
             info_base.type == TYPE_VALIABLE_RAW16 ||
             info_base.type == TYPE_VALIABLE_RAW32 )
    {
        info->type = UNPACK_TYPE_RAW;
        info->value.raw_value.size = info_base.value.size;
        info->value.raw_value.data = (buf + info_base.size);
        size += info_base.value.size;
    }
    return size;
    
}

