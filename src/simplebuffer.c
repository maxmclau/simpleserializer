#include <string.h>

#include "simplebuffer.h"

static size_t s_minimum_allocate_unit = 0;
static uint8_t* (*s_allocate_function)( size_t size ) = 0;
static void (*s_free_function)( void *buf ) = 0;

void simplebuffer_system_init( size_t _minimum_allocate_unit,
                               uint8_t* (*_allocate_function)( size_t size ),
                               void (*_free_function)( void * ) )
{
    s_minimum_allocate_unit = _minimum_allocate_unit;
    s_allocate_function = _allocate_function;
    s_free_function = _free_function;
}

void simplebuffer_init( simplebuffer *buf, uint8_t *data, size_t size )
{
    if( data == 0 && size == 0 )
    {
        memset( buf, 0, sizeof(simplebuffer) );
    }
    else
    {
        buf->size = size;
        buf->data = data;
        buf->alloc = 0;
    }
}

uint8_t* simplebuffer_checksize( simplebuffer *buf, size_t size )
{
    uint8_t* checked_buffer = NULL;
    if( buf->alloc < buf->size + size )
    {
        // Calc next alloction size.
        size_t unit = (size>s_minimum_allocate_unit) ? size : s_minimum_allocate_unit;
        size_t newsize = buf->size + size + unit;
        
        uint8_t *newdata = s_allocate_function( newsize );
        if( newdata == NULL )
        {
            return NULL;
        }
        if( buf->size != 0 )
        {
            memcpy( newdata, buf->data, buf->size );
        }

        /// Not allocated or given buffer.
        if( buf->alloc != 0 )
        {
            s_free_function( buf->data );
        }

        buf->data  = newdata;
        buf->alloc = newsize;
    }
    checked_buffer = buf->data + buf->size;
    buf->size += size;
    return checked_buffer;
}

bool simplebuffer_write( simplebuffer *buf, uint8_t* data, size_t size )
{
    size_t currentsize = buf->size;
    if( simplebuffer_checksize( buf, size ) )
    {
        memcpy( buf->data + currentsize, data, size );
        return true;
    }
    return false;
}

void simplebuffer_destroy( simplebuffer *buf )
{
    /// Not allocated or given buffer.
    if( buf->alloc != 0 ) 
    {
        s_free_function( buf->data );
    }
    simplebuffer_init( buf, NULL, 0 );
}

uint8_t* simplebuffer_release( simplebuffer *buf )
{
    uint8_t* data = buf->data;
    simplebuffer_init( buf, NULL, 0 );
    return data;
}
