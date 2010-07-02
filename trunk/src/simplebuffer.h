#ifndef H_SIMPLEBUFFER_H_100702080841__
#define H_SIMPLEBUFFER_H_100702080841__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// please define ALLOC and FREE macro before for your environment.

typedef struct simplebuffer {
	size_t size;  ///< サイズ
	uint8_t* data;   ///< データ
	size_t alloc; ///< 確保したサイズ
} simplebuffer;

void simplebuffer_init( simplebuffer *buf );
bool simplebuffer_checksize( simplebuffer *buf, size_t size );
void simplebuffer_destroy( simplebuffer *buf );




#endif //H_SIMPLEBUFFER_H_100702080841__
