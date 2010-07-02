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

int pack_nil( uint8_t* buffer );
int pack_bool( uint8_t* buffer, bool data );
int pack_fixuint( uint8_t* buffer, uint8_t data );
int pack_float( uint8_t* buffer, float data );
int pack_uint8( uint8_t* buffer, uint8_t data );
int pack_uint16( uint8_t* buffer, uint16_t data );
int pack_uint32( uint8_t* buffer, uint32_t data );
int pack_fixint( uint8_t* buffer, int8_t data );
int pack_int8( uint8_t* buffer, int8_t data );
int pack_int16( uint8_t* buffer, int16_t data );
int pack_int32( uint8_t* buffer, int32_t data );

int pack_uint( uint8_t* buffer, unsigned int data );
int pack_int( uint8_t* buffer, int data );
int pack_raw( uint8_t* buffer, uint8_t* data, size_t size );

#ifdef SUPPORT_64BIT_VALUE
int pack_double( uint8_t* buffer, double data );
#endif


#endif //H_PACK_H_100629195457__
