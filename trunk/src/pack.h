#ifndef H_PACK_H_100629195457__
#define H_PACK_H_100629195457__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// 
/// \brief Simple serializer.
/// 
/// This is very simple serializer for embedded use.
/// 

int pack_fixuint( unsigned char *buffer, uint8_t data );
int pack_uint8( unsigned char *buffer, uint8_t data );
int pack_uint16( unsigned char *buffer, uint16_t data );
int pack_uint32( unsigned char *buffer, uint32_t data );
int pack_fixint( unsigned char *buffer, int8_t data );
int pack_int8( unsigned char *buffer, int8_t data );
int pack_int16( unsigned char *buffer, int16_t data );
int pack_int32( unsigned char *buffer, int32_t data );

int pack_nil( unsigned char *buffer );
int pack_bool( unsigned char *buffer, bool data );
int pack_uint( unsigned char *buffer, unsigned int data );
int pack_int( unsigned char *buffer, int data );
int pack_raw( unsigned char *buffer, unsigned char *data, size_t size );

#endif //H_PACK_H_100629195457__
