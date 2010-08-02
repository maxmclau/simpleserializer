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

#include "test.hpp"
#include "test_data.h"

#include <cstdio>
TEST_F( SimpleserializerTest, pack_simplebuffer_text_test )
{
    simplebuffer text;
    simplebuffer serialized;

    serialized = pack_simplebuffer_text( (char*)"true, false, 0, 1, 2, 3, 4, 0xff, 0x100, -100, 1.1f,-100.1010101010, \"ABC\", a, b, c, d, 0x10" );
    text = unpack_simplebuffer_text( serialized );
    printf( "[%s]\n", (char*)text.data );
}

TEST_F( SimpleserializerTest, unpack_simplebuffer_text_test )
{
    simplebuffer serialized;
    simplebuffer text;

    simplebuffer_init( &serialized, (uint8_t*)numeric_data, sizeof( numeric_data ) );
    text = unpack_simplebuffer_text( serialized );
    ASSERT_EQ( strcmp( "false, true, "
                       "1234.500000f, -1234.500000f, 1234.123456lf, -1234.123456lf, "
                       "0u, 127u, 128u, 255u, "
                       "256u, 65535u, 65536u, 268435455u, "
                       "-1d, -32d, -33d, -128d, -129d, -32768d, -32769d, -134217728d",
                       (char *)text.data ), 0 );
    
    simplebuffer_init( &serialized, (uint8_t*)raw_data, sizeof( raw_data ) );
    text = unpack_simplebuffer_text( serialized );

    ASSERT_EQ( strcmp( "\"TEST\","
                       " \"012345678901234567890123456789\","
                       " \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcde\", ",
                       (char *)text.data ), 0 );

    simplebuffer_destroy( &serialized );
    simplebuffer_destroy( &text );
}

