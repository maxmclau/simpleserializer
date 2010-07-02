#include <boost/test/unit_test.hpp>
using boost::unit_test_framework::test_suite;

extern "C"
{
#include <simplebuffer.h>
}

#include <cstdio>
void simplebuffer_test( void )
{
    simplebuffer sbuf;
    bool result;

    simplebuffer_system_init( 1024u,
                              (uint8_t* (*)(size_t))malloc,
                              (void (*)(void*))free );

    simplebuffer_init( &sbuf );
    BOOST_CHECK_EQUAL( sbuf.size, 0u );
    BOOST_CHECK_EQUAL( sbuf.data, static_cast<uint8_t*>(0) );
    BOOST_CHECK_EQUAL( sbuf.alloc, 0u );
    
    result = simplebuffer_checksize( &sbuf, 10 );
    BOOST_CHECK_EQUAL( result, true );
    BOOST_CHECK_EQUAL( sbuf.size, 10u );
    BOOST_CHECK_NE( sbuf.data, static_cast<uint8_t*>(0) );
    BOOST_CHECK_GT( sbuf.alloc, 10u );

    for( int i = 0; i < 10; i++ )
    {
        *(sbuf.data + i) = static_cast<uint8_t>( 'A' + i );
    }
    BOOST_CHECK( memcmp( sbuf.data, "ABCDEFGHIJ", 10 ) == 0 );
    
    result = simplebuffer_write( &sbuf, (unsigned char*)"123456789", 10 );

    BOOST_CHECK( strcmp( (const char*)sbuf.data, "ABCDEFGHIJ123456789" ) == 0 );
    BOOST_CHECK_EQUAL( result, true );
    BOOST_CHECK_EQUAL( sbuf.size, 20u );
    BOOST_CHECK_GT( sbuf.alloc, 20u );

    result = simplebuffer_checksize( &sbuf, 20480 );
    BOOST_CHECK( strcmp( (const char*)sbuf.data, "ABCDEFGHIJ123456789" ) == 0 );
    BOOST_CHECK_GT( sbuf.alloc, 20500u );
    BOOST_CHECK_EQUAL( sbuf.size, 20500u );

    uint8_t* data = simplebuffer_release( &sbuf );
    BOOST_CHECK( strcmp( (const char*)data, "ABCDEFGHIJ123456789" ) == 0 );
    BOOST_CHECK_EQUAL( sbuf.size, 0u );
    BOOST_CHECK_EQUAL( sbuf.data, static_cast<uint8_t*>(0) );
    BOOST_CHECK_EQUAL( sbuf.alloc, 0u );

}
