#include "defines.h"
#include "unpack.h"

#include <stdint.h>

/// 16ビット値を取得
#define UNPACK_GET_16BIT_VALUE(d)         \
    ((uint16_t)(*d) << 8) |               \
    (uint16_t)(*(d+1))

/// 32ビット値を取得
#define UNPACK_GET_32BIT_VALUE(d)         \
    ((uint32_t)(*d) << 24)     |          \
    ((uint32_t)*(d+1) << 16) |            \
    ((uint32_t)*(d+2) <<  8) |            \
    (uint32_t)*(d+3)

unpack_info_t unpack( unsigned char *buf )
{
    unpack_info_t info = {0};
    unsigned char header = *buf++;

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
#if 0
    else if( header == TYPE_VALIABLE_FLOAT )
    {
    }
    else if( header == TYPE_VALIABLE_DOUBLE )
    {
    }
#endif
    else if( header == TYPE_VALIABLE_UINT8 )
    {
        info.size = 2;
        info.value.uint8_value = (uint8_t)(*buf);
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
#if 0
    else if( header == TYPE_VALIABLE_UINT64 )
    {
    }
#endif
    else if( header == TYPE_VALIABLE_INT8 )
    {
        info.size = 2;
        info.value.uint8_value = (int8_t)(*buf);
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

int unpack_ex( unpack_ex_info_t *info_ex, unsigned char *buf )
{
    unpack_info_t info = unpack( buf );
    int size = info.size;
    if( info.type == TYPE_VALIABLE_NIL )
    {
        info_ex->type = UNPACK_TYPE_NIL;
    }
    else if( info.type == TYPE_VALIABLE_FALSE )
    {
        info_ex->type = UNPACK_TYPE_BOOL;
        info_ex->value.bool_value = false;
    }
    else if( info.type == TYPE_VALIABLE_TRUE )
    {
        info_ex->type = UNPACK_TYPE_BOOL;
        info_ex->value.bool_value = true;
    }
    else if( info.type == TYPE_POSITIVE_FIXNUM || info.type == TYPE_VALIABLE_UINT8 )
    {
        info_ex->type = UNPACK_TYPE_UINT;
        info_ex->value.uint_value = (unsigned int)info.value.uint8_value;
    }
    else if( info.type == TYPE_VALIABLE_UINT16 )
    {
        info_ex->type = UNPACK_TYPE_UINT;
        info_ex->value.uint_value = (unsigned int)info.value.uint16_value;
    }
    else if( info.type == TYPE_VALIABLE_UINT32 )
    {
        info_ex->type = UNPACK_TYPE_UINT;
        info_ex->value.uint_value = (unsigned int)info.value.uint32_value;
    }
    else if( info.type == TYPE_NEGATIVE_FIXNUM || info.type == TYPE_VALIABLE_INT8 )
    {
        info_ex->type = UNPACK_TYPE_INT;
        info_ex->value.int_value = (int)info.value.int8_value;
    }
    else if( info.type == TYPE_VALIABLE_INT16 )
    {
        info_ex->type = UNPACK_TYPE_INT;
        info_ex->value.int_value = (int)info.value.int16_value;
    }
    else if( info.type == TYPE_VALIABLE_INT32 )
    {
        info_ex->type = UNPACK_TYPE_INT;
        info_ex->value.int_value = (int)info.value.int32_value;
    }
    else if( info.type == TYPE_FIXROW ||
             info.type == TYPE_VALIABLE_RAW16 ||
             info.type == TYPE_VALIABLE_RAW32 )
    {
        info_ex->type = UNPACK_TYPE_RAW;
        info_ex->value.raw_value.size = info.value.size;
        info_ex->value.raw_value.data = (buf + info.size);
        size += info.value.size;
    }
    return size;
    
}

