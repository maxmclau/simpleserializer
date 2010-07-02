#include <string.h>

#include "simplebuffer.h"

#ifndef MINIMUM_ALLOCATE_UNIT
#define MINIMUM_ALLOCATE_UNIT (1024)
#endif

#ifndef MALLOC
#define MALLOC(xSize) (uint8_t*)malloc(xSize)
#endif

#ifndef FREE
#define FREE(xBuf) free(xBuf)
#endif

void simplebuffer_init( simplebuffer *buf )
{
    memset( buf, 0, sizeof(simplebuffer) );
}

bool simplebuffer_checksize( simplebuffer *buf, size_t size )
{
    if( buf->alloc < buf->size + size )
    {
        size_t newsize = buf->size + size + MINIMUM_ALLOCATE_UNIT;
        uint8_t *newdata = MALLOC( newsize );
        if( newdata == NULL )
        {
            return false;
        }
        if( buf->size != 0 )
        {
            memcpy( newdata, buf->data, buf->size );
        }
        FREE( buf->data );
        buf->size += size;
        buf->data  = newdata;
        buf->alloc = newsize;
    }
    return true;
}

void simplebuffer_destroy( simplebuffer *buf )
{
    if( buf->data != NULL )
    {
        FREE( buf->data );
    }
    simplebuffer_init( buf );
}


