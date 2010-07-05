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
#include "pack_simplebuffer.h"

bool pack_simplebuffer_fixuint( simplebuffer* buffer, uint8_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 1);
    if( buf != NULL )
    {
        pack_fixuint( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint8( simplebuffer* buffer, uint8_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 2);
    if( buf != NULL )
    {
        pack_uint8( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint16( simplebuffer* buffer, uint16_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 3);
    if( buf != NULL )
    {
        pack_uint16( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint32( simplebuffer* buffer, uint32_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 5);
    if( buf != NULL )
    {
        pack_uint32( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_fixint( simplebuffer* buffer, int8_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 1);
    if( buf != NULL )
    {
        pack_fixint( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_int8( simplebuffer* buffer, int8_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 2);
    if( buf != NULL )
    {
        pack_int8( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_int16( simplebuffer* buffer, int16_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 3);
    if( buf != NULL )
    {
        pack_int16( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_int32( simplebuffer* buffer, int32_t data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 5);
    if( buf != NULL )
    {
        pack_int32( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_nil( simplebuffer* buffer )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 1);
    if( buf != NULL )
    {
        *buf = TYPE_VALIABLE_NIL;
        return true;
    }
    return false;
}

bool pack_simplebuffer_bool( simplebuffer* buffer, bool data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 1);
    if( buf != NULL )
    {
        if( data )
        {
            *buf = TYPE_VALIABLE_TRUE;
        }
        else
        {
            *buf = TYPE_VALIABLE_FALSE;
        }
        return true;
    }
    return false;
}

bool pack_simplebuffer_float( simplebuffer* buffer, float data )
{
    uint8_t *buf = simplebuffer_checksize( buffer, 5);
    if( buf != NULL )
    {
        pack_float( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint( simplebuffer* buffer, unsigned int data )
{
    if( data < 0x80 )
    {
        return pack_simplebuffer_fixuint( buffer, (uint8_t)data );
    }
    else if( data <= UINT8_MAX )
    {
        return pack_simplebuffer_uint8( buffer, (uint8_t)data );
    }
    else if( data <= UINT16_MAX )
    {
        return pack_simplebuffer_uint16( buffer, (uint16_t)data );
    }
    else
    {
        return pack_simplebuffer_uint32( buffer, (uint32_t)data );
    }
}

bool pack_simplebuffer_int( simplebuffer* buffer, int data )
{
    if( data >= 0 )
    {
        return pack_simplebuffer_uint( buffer, (unsigned int)data );
    }
    else if( data >= -32 )
    {
        return pack_simplebuffer_fixint( buffer, (int8_t)data );
    }
    else if( data >= INT8_MIN )
    {
        return pack_simplebuffer_int8( buffer, (int8_t)data );
    }
    else if( data >= INT16_MIN )
    {
        return pack_simplebuffer_int16( buffer, (int16_t)data );
    }
    else
    {
        return pack_simplebuffer_int32( buffer, (int32_t)data );
    }
}

bool pack_simplebuffer_raw( simplebuffer* buffer, uint8_t* data, size_t data_size )
{
    uint8_t *buf = buffer->data + buffer->size;
    size_t size = 0;
    if( data_size < 32 )           {size = 1;}
    else if( data_size < 0x10000 ) {size = 3;}
    else                           {size = 5;}

    buf = simplebuffer_checksize( buffer, size + data_size);
    if( buf != NULL )
    {
        pack_raw( buf, data, data_size );
        return true;
    }
    
    return false;
}

#ifdef SUPPORT_64BIT_VALUE
bool pack_simplebuffer_double( simplebuffer* buffer, double data )
{
    uint8_t* buf = simplebuffer_checksize( buffer, 9);
    if( buf != NULL )
    {
        pack_double( buf, data );
        return true;
    }
    return false;
}
#endif

