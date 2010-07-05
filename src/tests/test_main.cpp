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
using namespace boost::unit_test_framework;

// serilizer tests.
void pack_test_numeric( void );
void pack_test_raw( void );
void pack_test_raw32( void );

void unpack_base_test_numeric( void );
void unpack_base_test_raw( void );

void unpack_test( void );
void unpack_test_raw32( void );

// simplebuffer tests.
void simplebuffer_test( void );

// simplebuffer_serialize tests.
void pack_simplebuffer_test_numeric( void );
void pack_simplebuffer_test_raw( void );
void pack_simplebuffer_test_raw32( void );

bool init_function()
{
    test_suite *pack_tests = BOOST_TEST_SUITE( "pack_tests" );
    pack_tests->add( BOOST_TEST_CASE(&pack_test_numeric) );
    pack_tests->add( BOOST_TEST_CASE(&pack_test_raw) );
    pack_tests->add( BOOST_TEST_CASE(&pack_test_raw32) );
    framework::master_test_suite().add( pack_tests );
    

    test_suite *unpack_tests = BOOST_TEST_SUITE( "unpack_tests" );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_base_test_numeric) );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_base_test_raw) );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_test) );
    unpack_tests->add( BOOST_TEST_CASE(&unpack_test_raw32) );
    framework::master_test_suite().add( unpack_tests );

    test_suite *simplebuffer_tests = BOOST_TEST_SUITE( "simplebuffer_tests" );
    simplebuffer_tests->add( BOOST_TEST_CASE(&simplebuffer_test) );
    framework::master_test_suite().add( simplebuffer_tests );

    test_suite *simplebuffer_serialize_tests = BOOST_TEST_SUITE( "simplebuffer_serialize_tests" );
    simplebuffer_serialize_tests->add( BOOST_TEST_CASE(&pack_simplebuffer_test_numeric) );
    simplebuffer_serialize_tests->add( BOOST_TEST_CASE(&pack_simplebuffer_test_raw) );
    simplebuffer_serialize_tests->add( BOOST_TEST_CASE(&pack_simplebuffer_test_raw32) );
    framework::master_test_suite().add( simplebuffer_serialize_tests );

    return true;
}

int main( int argc, char* argv[] )
{
    return ::boost::unit_test::unit_test_main( &init_function, argc, argv );
}

