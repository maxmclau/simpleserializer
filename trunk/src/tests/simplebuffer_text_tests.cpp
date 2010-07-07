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

#include <boost/test/unit_test.hpp>
#include <float.h>

using boost::unit_test_framework::test_suite;

extern "C"
{
#include <pack_simplebuffer_text.h>
#include <unpack_simplebuffer_text.h>

#include "../serializer/defines.h"
}

#include "test_data.h"

void pack_simplebuffer_text_test( void )
{
}

#include <cstdio>
void unpack_simplebuffer_text_test( void )
{
    simplebuffer serialized;
    simplebuffer text;
    simplebuffer_init( &serialized, (uint8_t*)numeric_data, sizeof( numeric_data ) );
    text = unpack_simplebuffer_text( serialized );
    printf( "[%s]\n", text.data );
    
    simplebuffer_init( &serialized, (uint8_t*)raw_data, sizeof( raw_data ) );
    text = unpack_simplebuffer_text( serialized );
    printf( "[%s]\n", text.data );
    
}

