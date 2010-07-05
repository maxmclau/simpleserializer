#ifndef H_SIMPLEBUFFER_H_100702080841__
#define H_SIMPLEBUFFER_H_100702080841__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


/// \brief Simple buffer has variable length.
/// 
/// This is very simple implementation of variable length buffer on C.
/// simplebuffer could be handle both allocated buffer and self-allocate buffer.
/// 
/// - Allocated buffer is given buffer from simplebuffer user.
/// - Self allocate buffer is auto allocated data.
void simplebuffer_system_init( size_t _minimum_allocate_unit,
                               uint8_t* (*_allocate_function)( size_t size ),
                               void (*_free_function)( void * ) );

typedef struct simplebuffer {
	size_t size;     ///< Used size.
	uint8_t* data;   ///< Data buffer.
	size_t alloc;    ///< Allocated size.
} simplebuffer;

/// \brief Initialize 
void simplebuffer_init( simplebuffer *buf, uint8_t *data, size_t size );

/// \brief Check and re-allocate buffer.
bool simplebuffer_checksize( simplebuffer *buf, size_t size );

/// \brief Add data into buffer.
bool simplebuffer_write( simplebuffer *buf, uint8_t* data, size_t size );

/// \brief Clear sizes and free buffer.
void simplebuffer_destroy( simplebuffer *buf );

/// \brief get data from simplebuffer and clear simplebuffer.
uint8_t* simplebuffer_release( simplebuffer *buf );



#endif //H_SIMPLEBUFFER_H_100702080841__
