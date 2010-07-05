#include "defines.h"
#include "pack_simplebuffer.h"

bool pack_simplebuffer_fixuint( simplebuffer* buffer, uint8_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 1) )
    {
        pack_fixuint( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint8( simplebuffer* buffer, uint8_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 2) )
    {
        pack_uint8( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint16( simplebuffer* buffer, uint16_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 3) )
    {
        pack_uint16( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_uint32( simplebuffer* buffer, uint32_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 5) )
    {
        pack_uint32( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_fixint( simplebuffer* buffer, int8_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 1) )
    {
        pack_fixint( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_int8( simplebuffer* buffer, int8_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 2) )
    {
        pack_int8( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_int16( simplebuffer* buffer, int16_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 3) )
    {
        pack_int16( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_int32( simplebuffer* buffer, int32_t data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 5) )
    {
        pack_int32( buf, data );
        return true;
    }
    return false;
}

bool pack_simplebuffer_nil( simplebuffer* buffer )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 1) )
    {
        *buf = TYPE_VALIABLE_NIL;
        return true;
    }
    return false;
}

bool pack_simplebuffer_bool( simplebuffer* buffer, bool data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 1) )
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
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 5) )
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
    if( simplebuffer_checksize( buffer, size + data_size) )
    {
        pack_raw( buf, data, data_size );
        return true;
    }
    
    return false;
}


#ifdef SUPPORT_64BIT_VALUE
bool pack_simplebuffer_double( simplebuffer* buffer, double data )
{
    uint8_t *buf = buffer->data + buffer->size;
    if( simplebuffer_checksize( buffer, 9) )
    {
        pack_double( buf, data );
        return true;
    }
    return false;
}
#endif

