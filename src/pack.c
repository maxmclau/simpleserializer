#include "defines.h"
#include "pack.h"

#include <string.h>

#define PACK_8BIT_VALUE( xBuf, xData )          \
    *xBuf++ = (unsigned char)((uint8_t)xData);

#define PACK_16BIT_VALUE( xBuf, xData )                 \
    *xBuf++ = (unsigned char)((uint16_t)xData >> 8);    \
    *xBuf++ = (unsigned char)((uint16_t)xData);  
    
#define PACK_32BIT_VALUE( xBuf, xData )                  \
    *xBuf++ = (unsigned char)((uint32_t)xData >> 24);    \
    *xBuf++ = (unsigned char)((uint32_t)xData >> 16);    \
    *xBuf++ = (unsigned char)((uint32_t)xData >> 8);     \
    *xBuf++ = (unsigned char)((uint32_t)xData);  
    

int pack_fixuint( unsigned char *buffer, uint8_t data )
{
    PACK_8BIT_VALUE( buffer, data );
    return 1;
}

int pack_uint8( unsigned char *buffer, uint8_t data )
{
    *buffer++ = TYPE_VALIABLE_UINT8;
    PACK_8BIT_VALUE( buffer, data );
    return 2;
}

int pack_uint16( unsigned char *buffer, uint16_t data )
{
    *buffer++ = TYPE_VALIABLE_UINT16;
    PACK_16BIT_VALUE( buffer, data );
    return 3;
}

int pack_uint32( unsigned char *buffer, uint32_t data )
{
    *buffer++ = TYPE_VALIABLE_UINT32;
    PACK_32BIT_VALUE( buffer, data );
    return 5;
}

int pack_fixint( unsigned char *buffer, int8_t data )
{
    PACK_8BIT_VALUE( buffer, (TYPE_FIXROW | (unsigned char)data) );
    return 1;
}

int pack_int8( unsigned char *buffer, int8_t data )
{
    *buffer++ = TYPE_VALIABLE_INT8;
    PACK_8BIT_VALUE( buffer, data );
    return 2;
}

int pack_int16( unsigned char *buffer, int16_t data )
{
    *buffer++ = TYPE_VALIABLE_INT16;
    PACK_16BIT_VALUE( buffer, data );
    return 3;
}

int pack_int32( unsigned char *buffer, int32_t data )
{
    *buffer++ = TYPE_VALIABLE_INT32;
    PACK_32BIT_VALUE( buffer, data );
    return 5;
}

int pack_nil( unsigned char *buffer )
{
    *buffer = TYPE_VALIABLE_NIL;
    return 1;
}

int pack_bool( unsigned char *buffer, bool data )
{
    if( data )
    {
        *buffer = TYPE_VALIABLE_TRUE;
    }
    else
    {
        *buffer = TYPE_VALIABLE_FALSE;
    }
    return 1;
}

int pack_uint( unsigned char *buffer, unsigned int data )
{
    if( data < 0x80 )
    {
        return pack_fixuint( buffer, (uint8_t)data );
    }
    else if( data < 0x100 )
    {
        return pack_uint8( buffer, (uint8_t)data );
    }
    else if( data < 0x10000 )
    {
        return pack_uint16( buffer, (uint16_t)data );
    }
    else
    {
        return pack_uint32( buffer, (uint32_t)data );
    }
}

int pack_int(  unsigned char *buffer, int data )
{
    if( data >= 0 )
    {
        return pack_uint( buffer, (unsigned int)data );
    }
    else if( data >= -32 )
    {
        return pack_fixint( buffer, (int8_t)data );
    }
    else if( data >= -128 )
    {
        return pack_int8( buffer, (int8_t)data );
    }
    else if( data >= -32768 )
    {
        return pack_int16( buffer, (int16_t)data );
    }
    else
    {
        return pack_int32( buffer, (int32_t)data );
    }
}

int pack_raw( unsigned char *buffer, unsigned char *data, size_t data_size )
{
    int size = 0;
    if( data_size < 32 )
    {
        *buffer++ = TYPE_FIXROW | (unsigned char)data_size;
        size = 1;
    }
    else if( data_size < 0x10000 )
    {
        *buffer++ = TYPE_VALIABLE_RAW16;
        PACK_16BIT_VALUE( buffer, data_size );
        size = 3;
    }
    else
    {
        *buffer++ = TYPE_VALIABLE_RAW32;
        PACK_32BIT_VALUE( buffer, data_size );
        size = 5;
    }
    memcpy( buffer, data, data_size );
    size += data_size;
    return size;
}

