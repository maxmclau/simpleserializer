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
    simplebuffer_init( &sbuf );
    BOOST_CHECK_EQUAL( sbuf.size, 0u );
    BOOST_CHECK_EQUAL( sbuf.data, static_cast<uint8_t*>(0) );
    BOOST_CHECK_EQUAL( sbuf.alloc, 0u );
    
    bool result = simplebuffer_checksize( &sbuf, 10 );
    BOOST_CHECK_EQUAL( result, true );
    BOOST_CHECK_EQUAL( sbuf.size, 10u );
    BOOST_CHECK_NE( sbuf.data, static_cast<uint8_t*>(0) );
    BOOST_CHECK_EQUAL( sbuf.alloc, 1034u );
    

}
