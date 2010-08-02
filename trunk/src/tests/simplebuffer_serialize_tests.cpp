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

TEST_F( SimpleserializerTest, pack_simplebuffer_test_numeric )
{
    simplebuffer buf;
    bool result;

    simplebuffer_init( &buf, NULL, 0 );

    result = pack_simplebuffer_nil( &buf );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_bool( &buf, false );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_bool( &buf, true );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_float( &buf, 1234.5 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_float( &buf, -1234.5 );
    ASSERT_EQ(result, true);
#ifdef SUPPORT_64BIT_VALUE
    result = pack_simplebuffer_double( &buf, 1234.123456 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_double( &buf, -1234.123456 );
    ASSERT_EQ(result, true);
#endif
    result = pack_simplebuffer_fixuint( &buf, 0 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_fixuint( &buf, 127 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_uint8( &buf, 128 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_uint8( &buf, 255 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_uint16( &buf, 256 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_uint16( &buf, 65535 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_uint32( &buf, 65536 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_uint32( &buf, 268435455 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_fixint( &buf, -1 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_fixint( &buf, -32 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_int8( &buf, -33 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_int8( &buf, -128 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_int16( &buf, -129 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_int16( &buf, -32768 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_int32( &buf, -32769 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_int32( &buf, -134217728 );
    ASSERT_EQ(result, true);

    ASSERT_EQ(buf.size, sizeof( numeric_data ));
    ASSERT_EQ(memcmp( numeric_data, buf.data, sizeof( numeric_data ) ), 0);

    simplebuffer_destroy( &buf );
}

TEST_F( SimpleserializerTest, pack_simplebuffer_test_raw )
{
    simplebuffer buf;
    bool result;

    simplebuffer_init( &buf, NULL, 0 );

    result = pack_simplebuffer_raw( &buf, (unsigned char *)"TEST", 5 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_raw( &buf, (unsigned char *)"012345678901234567890123456789", 31 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_raw( &buf, (unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcde", 32 );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_nil( &buf );
    ASSERT_EQ(result, true);
    
    ASSERT_EQ(buf.size, sizeof(raw_data));
    ASSERT_EQ(memcmp( buf.data, raw_data, sizeof(raw_data) ), 0);

    simplebuffer_destroy( &buf );
}

TEST_F( SimpleserializerTest, pack_simplebuffer_test_raw32 )
{
    int data_size = 131072;
    unsigned char *test_data = (unsigned char *)malloc( data_size );
    simplebuffer buf;
    bool result;

    for( int i = 0; i < data_size; i++ )
    {
        *(test_data+i) = i & 0xff;
    }

    simplebuffer_init( &buf, NULL, 0 );

    result = pack_simplebuffer_raw( &buf, test_data, data_size );
    ASSERT_EQ(result, true);
    result = pack_simplebuffer_nil( &buf );
    ASSERT_EQ(result, true);

    ASSERT_EQ( *(buf.data),     0xdb );
    ASSERT_EQ( *((buf.data)+1), 0x00 );
    ASSERT_EQ( *((buf.data)+2), 0x02 );
    ASSERT_EQ( *((buf.data)+3), 0x00 );
    ASSERT_EQ( *((buf.data)+4), 0x00 );
    ASSERT_EQ( memcmp( test_data, (buf.data)+5, data_size ), 0 );
    ASSERT_EQ( *((buf.data)+5+data_size), 0xC0 );

    free(test_data);
    simplebuffer_destroy( &buf );
}

