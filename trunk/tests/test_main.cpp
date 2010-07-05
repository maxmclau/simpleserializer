#include <boost/test/unit_test.hpp>
using namespace boost::unit_test_framework;

// serilizer tests.
void pack_test_numeric( void );
void unpack_test_numeric( void );
void pack_test_raw( void );
void unpack_test_raw( void );
void pack_test_raw32( void );
void unpack_test_raw32( void );
void unpack_ex_test( void );

// simplebuffer tests.
void simplebuffer_test( void );

// simplebuffer_serialize tests.
void pack_simplebuffer_test_numeric( void );

bool init_function()
{
    test_suite *pack_tests = BOOST_TEST_SUITE( "pack_tests" );
    pack_tests->add( BOOST_TEST_CASE(&pack_test_numeric) );
    pack_tests->add( BOOST_TEST_CASE(&pack_test_raw) );
    pack_tests->add( BOOST_TEST_CASE(&pack_test_raw32) );
    framework::master_test_suite().add( pack_tests );
    

    test_suite *unpack_tests = BOOST_TEST_SUITE( "unpack_tests" );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_test_numeric) );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_test_raw) );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_test_raw32) );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_ex_test) );
    framework::master_test_suite().add( unpack_tests );

    test_suite *simplebuffer_tests = BOOST_TEST_SUITE( "simplebuffer_tests" );
    simplebuffer_tests->add( BOOST_TEST_CASE(&simplebuffer_test) );
    framework::master_test_suite().add( simplebuffer_tests );

    test_suite *simplebuffer_serialize_tests = BOOST_TEST_SUITE( "simplebuffer_serialize_tests" );
    simplebuffer_serialize_tests->add( BOOST_TEST_CASE(&pack_simplebuffer_test_numeric) );
    framework::master_test_suite().add( simplebuffer_serialize_tests );

    return true;
}

int main( int argc, char* argv[] )
{
    return ::boost::unit_test::unit_test_main( &init_function, argc, argv );
}

