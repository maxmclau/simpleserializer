#ifndef H_PACK_SIMPLEBUFFER_H_100702184853__
#define H_PACK_SIMPLEBUFFER_H_100702184853__

#include "pack.h"
#include "simplebuffer.h"

bool pack_simplebuffer_fixuint( simplebuffer* buffer, uint8_t data );
bool pack_simplebuffer_uint8( simplebuffer* buffer, uint8_t data );
bool pack_simplebuffer_uint16( simplebuffer* buffer, uint16_t data );
bool pack_simplebuffer_uint32( simplebuffer* buffer, uint32_t data );
bool pack_simplebuffer_fixint( simplebuffer* buffer, int8_t data );
bool pack_simplebuffer_int8( simplebuffer* buffer, int8_t data );
bool pack_simplebuffer_int16( simplebuffer* buffer, int16_t data );
bool pack_simplebuffer_int32( simplebuffer* buffer, int32_t data );

bool pack_simplebuffer_nil( simplebuffer* buffer );
bool pack_simplebuffer_bool( simplebuffer* buffer, bool data );
bool pack_simplebuffer_float( simplebuffer* buffer, float data );
bool pack_simplebuffer_uint( simplebuffer* buffer, unsigned int data );
bool pack_simplebuffer_int( simplebuffer* buffer, int data );
bool pack_simplebuffer_raw( simplebuffer* buffer, uint8_t* data, size_t size );

#ifdef SUPPORT_64BIT_VALUE
bool pack_simplebuffer_double( simplebuffer* buffer, double data );
#endif

#endif //H_PACK_SIMPLEBUFFER_H_100702184853__
