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

#ifdef SUPPORT_64BIT_VALUE
#define PACK_64BIT_VALUE( xBuf, xData )                  \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 56);    \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 48);    \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 40);    \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 32);    \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 24);    \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 16);    \
    *xBuf++ = (unsigned char)((uint64_t)xData >> 8);     \
    *xBuf++ = (unsigned char)((uint64_t)xData);  
#endif    

int pack_nil( uint8_t* buffer )
{
    *buffer = TYPE_VALIABLE_NIL;
    return 1;
}

int pack_bool( uint8_t* buffer, bool data )
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

int pack_float( uint8_t* buffer, float data )
{
	union { float f; uint32_t i; } mem;
	mem.f = data;
    *buffer++ = TYPE_VALIABLE_FLOAT;
    PACK_32BIT_VALUE( buffer, mem.i );
    return 5;
}

int pack_fixuint( uint8_t* buffer, uint8_t data )
{
    PACK_8BIT_VALUE( buffer, data );
    return 1;
}

int pack_uint8( uint8_t* buffer, uint8_t data )
{
    *buffer++ = TYPE_VALIABLE_UINT8;
    PACK_8BIT_VALUE( buffer, data );
    return 2;
}

int pack_uint16( uint8_t* buffer, uint16_t data )
{
    *buffer++ = TYPE_VALIABLE_UINT16;
    PACK_16BIT_VALUE( buffer, data );
    return 3;
}

int pack_uint32( uint8_t* buffer, uint32_t data )
{
    *buffer++ = TYPE_VALIABLE_UINT32;
    PACK_32BIT_VALUE( buffer, data );
    return 5;
}

int pack_fixint( uint8_t* buffer, int8_t data )
{
    PACK_8BIT_VALUE( buffer, (TYPE_FIXROW | (unsigned char)data) );
    return 1;
}

int pack_int8( uint8_t* buffer, int8_t data )
{
    *buffer++ = TYPE_VALIABLE_INT8;
    PACK_8BIT_VALUE( buffer, data );
    return 2;
}

int pack_int16( uint8_t* buffer, int16_t data )
{
    *buffer++ = TYPE_VALIABLE_INT16;
    PACK_16BIT_VALUE( buffer, data );
    return 3;
}

int pack_int32( uint8_t* buffer, int32_t data )
{
    *buffer++ = TYPE_VALIABLE_INT32;
    PACK_32BIT_VALUE( buffer, data );
    return 5;
}

int pack_uint( uint8_t* buffer, unsigned int data )
{
    if( data < 0x80 )
    {
        return pack_fixuint( buffer, (uint8_t)data );
    }
    else if( data <= UINT8_MAX )
    {
        return pack_uint8( buffer, (uint8_t)data );
    }
    else if( data <= UINT16_MAX )
    {
        return pack_uint16( buffer, (uint16_t)data );
    }
    else
    {
        return pack_uint32( buffer, (uint32_t)data );
    }
}

int pack_int(  uint8_t* buffer, int data )
{
    if( data >= 0 )
    {
        return pack_uint( buffer, (unsigned int)data );
    }
    else if( data >= -32 )
    {
        return pack_fixint( buffer, (int8_t)data );
    }
    else if( data >= INT8_MIN )
    {
        return pack_int8( buffer, (int8_t)data );
    }
    else if( data >= INT16_MIN )
    {
        return pack_int16( buffer, (int16_t)data );
    }
    else
    {
        return pack_int32( buffer, (int32_t)data );
    }
}

int pack_raw( uint8_t* buffer, uint8_t* data, size_t data_size )
{
    int size = 0;
    size = pack_raw_header( buffer, data_size );
    memcpy( buffer+size, data, data_size );
    size += data_size;
    return size;
}

int pack_raw_header( uint8_t* buffer, size_t data_size )
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
    return size;
}

int pack_array_header( uint8_t* buffer, size_t size )
{
    return 0;
}

int pack_map_header( uint8_t* buffer, size_t size )
{
    return 0;
}

#ifdef SUPPORT_64BIT_VALUE
int pack_double( uint8_t* buffer, double data )
{
	union { double d; uint64_t i; } mem;
	mem.d = data;
    *buffer++ = TYPE_VALIABLE_DOUBLE;
    PACK_64BIT_VALUE( buffer, mem.i );
    return 9;
}
#endif

