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
