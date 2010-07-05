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

int pack_fixuint( uint8_t* buffer, uint8_t data );
int pack_uint8( uint8_t* buffer, uint8_t data );
int pack_uint16( uint8_t* buffer, uint16_t data );
int pack_uint32( uint8_t* buffer, uint32_t data );
int pack_fixint( uint8_t* buffer, int8_t data );
int pack_int8( uint8_t* buffer, int8_t data );
int pack_int16( uint8_t* buffer, int16_t data );
int pack_int32( uint8_t* buffer, int32_t data );

int pack_nil( uint8_t* buffer );
int pack_bool( uint8_t* buffer, bool data );
int pack_float( uint8_t* buffer, float data );
int pack_uint( uint8_t* buffer, unsigned int data );
int pack_int( uint8_t* buffer, int data );
int pack_raw( uint8_t* buffer, uint8_t* data, size_t size );

#ifdef SUPPORT_64BIT_VALUE
int pack_double( uint8_t* buffer, double data );
#endif


#endif //H_PACK_H_100629195457__
