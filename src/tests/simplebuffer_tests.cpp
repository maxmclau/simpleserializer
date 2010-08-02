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

extern "C"
{
#include <simplebuffer.h>
}

#include "test.hpp"

#include <cstdio>
TEST_F( SimpleserializerTest, simplebuffer_test )
{
    simplebuffer sbuf;
    uint8_t* data;

    simplebuffer_system_init( 1024u,
                              (uint8_t* (*)(size_t))malloc,
                              (void (*)(void*))free );

    simplebuffer_init( &sbuf, (uint8_t*)"TEST", 5 );
    ASSERT_TRUE( memcmp( sbuf.data, "TEST", 5 ) == 0 );
    simplebuffer_destroy( &sbuf );
    ASSERT_EQ( sbuf.size, 0u );
    ASSERT_EQ( sbuf.data, static_cast<uint8_t*>(0) );
    ASSERT_EQ( sbuf.alloc, 0u );

    bool result;
    simplebuffer_init( &sbuf, (uint8_t*)"TEST", 4 );
    result = simplebuffer_write( &sbuf, (unsigned char*)"123456789", 9 );
    result = simplebuffer_write( &sbuf, (unsigned char*)"", 1 );
    data = simplebuffer_release( &sbuf );
    ASSERT_TRUE( memcmp( data, "TEST123456789", 14 ) == 0 );
    ASSERT_EQ( sbuf.size, 0u );
    ASSERT_EQ( sbuf.data, static_cast<uint8_t*>(0) );
    ASSERT_EQ( sbuf.alloc, 0u );
    

    simplebuffer_init( &sbuf, NULL, 0 );
    ASSERT_EQ( sbuf.size, 0u );
    ASSERT_EQ( sbuf.data, static_cast<uint8_t*>(0) );
    ASSERT_EQ( sbuf.alloc, 0u );
    
    data = simplebuffer_checksize( &sbuf, 10 );
    ASSERT_NE( data, (void *)0 );
    ASSERT_EQ( sbuf.size, 10u );
    ASSERT_NE( sbuf.data, static_cast<uint8_t*>(0) );
    ASSERT_GT( sbuf.alloc, 10u );

    for( int i = 0; i < 10; i++ )
    {
        *(sbuf.data + i) = static_cast<uint8_t>( 'A' + i );
    }
    ASSERT_TRUE( memcmp( sbuf.data, "ABCDEFGHIJ", 10 ) == 0 );
    
    result = simplebuffer_write( &sbuf, (unsigned char*)"123456789", 10 );

    ASSERT_TRUE( strcmp( (const char*)sbuf.data, "ABCDEFGHIJ123456789" ) == 0 );
    ASSERT_EQ( result, true );
    ASSERT_EQ( sbuf.size, 20u );
    ASSERT_GT( sbuf.alloc, 20u );

    data = simplebuffer_checksize( &sbuf, 20480 );
    ASSERT_NE( data, (void *)0 );
    ASSERT_TRUE( strcmp( (const char*)sbuf.data, "ABCDEFGHIJ123456789" ) == 0 );
    ASSERT_GT( sbuf.alloc, 20500u );
    ASSERT_EQ( sbuf.size, 20500u );

    data = simplebuffer_release( &sbuf );
    ASSERT_TRUE( strcmp( (const char*)data, "ABCDEFGHIJ123456789" ) == 0 );
    ASSERT_EQ( sbuf.size, 0u );
    ASSERT_EQ( sbuf.data, static_cast<uint8_t*>(0) );
    ASSERT_EQ( sbuf.alloc, 0u );

}
