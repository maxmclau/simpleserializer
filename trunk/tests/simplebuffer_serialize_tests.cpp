#include <boost/test/unit_test.hpp>
#include <float.h>

using boost::unit_test_framework::test_suite;

extern "C"
{
#include "pack_simplebuffer.h"

#include "defines.h"
}

static const unsigned char numeric_data[] = {
    0xC0,                            // NIL
    0xC4,                            // FALSE
    0xC8,                            // TRUE
    0xCA, 0x7E, 0xFF, 0xFF, 0xFF,    // FLOAT  FLT_MAX/2
    0xCA, 0x00, 0x40, 0x00, 0x00,    // FLOAT  FLT_MIN/2
#ifdef SUPPORT_64BIT_VALUE
    0xCB, 0x7F, 0xF0, 0x00, 0x00,    // DOUBLE FLT_MAX*2
    0x00, 0x00, 0x00, 0x00,
    0xCB, 0x38, 0x20, 0x00, 0x00,    // DOUBLE FLT_MIN*2
    0x00, 0x00, 0x00, 0x00,
#endif
    0x00,                            // FIXUINT 0
    0x7F,                            // FIXUINT 127
    0xCC, 0x80,                      // UINT8 128
    0xCC, 0xFF,                      // UINT8 255
    0xCD, 0x01, 0x00,                // UINT16 256
    0xCD, 0xFF, 0xFF,                // UINT16 65535
    0xCE, 0x00, 0x01, 0x00, 0x00,    // UINT32 65536
    0xCE, 0x0F, 0xFF, 0xFF, 0xFF,    // UINT32 268435455
    0xFF,                            // FIXINT -1
    0xE0,                            // FIXINT -32
    0xD0, 0xDF,                      // INT8 -33
    0xD0, 0x80,                      // INT8 -128
    0xD1, 0xFF, 0x7F,                // INT16 -129
    0xD1, 0x80, 0x00,                // INT16 -32768
    0xD2, 0xFF, 0xFF, 0x7F, 0xFF,    // INT32 -32769
    0xD2, 0xF8, 0x00, 0x00, 0x00     // INT32 -134217728
};

static unsigned char raw_data[] = {
    // "TEST"
    0xA5, 0x54, 0x45, 0x53, 0x54, 0x00,

    // "012345678901234567890123456789"
    0xBF, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34,
    0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32,
    0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x00,

    // "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde"
    0xC1, 0x00, 0x20, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
    0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
    0x56, 0x57, 0x58, 0x59, 0x5A, 0x61, 0x62, 0x63,
    0x64, 0x65, 0x00,

    // NIL
    0xC0
};

void pack_simplebuffer_test_numeric( void )
{
    simplebuffer buf;
    bool result;
    simplebuffer_system_init( 1024u,
                              (uint8_t* (*)(size_t))malloc,
                              (void (*)(void*))free );

    simplebuffer_init( &buf, NULL, 0 );

    result = pack_simplebuffer_nil( &buf );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_bool( &buf, false );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_bool( &buf, true );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_float( &buf, FLT_MAX/2 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_float( &buf, FLT_MIN/2 );
    BOOST_CHECK_EQUAL(result, true);
#ifdef SUPPORT_64BIT_VALUE
    result = pack_simplebuffer_double( &buf, FLT_MAX*2 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_double( &buf, FLT_MIN*2 );
    BOOST_CHECK_EQUAL(result, true);
#endif
    result = pack_simplebuffer_fixuint( &buf, 0 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_fixuint( &buf, 127 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_uint8( &buf, 128 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_uint8( &buf, 255 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_uint16( &buf, 256 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_uint16( &buf, 65535 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_uint32( &buf, 65536 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_uint32( &buf, 268435455 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_fixint( &buf, -1 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_fixint( &buf, -32 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_int8( &buf, -33 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_int8( &buf, -128 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_int16( &buf, -129 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_int16( &buf, -32768 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_int32( &buf, -32769 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_int32( &buf, -134217728 );
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(buf.size, sizeof( numeric_data ));
    BOOST_CHECK_EQUAL(memcmp( numeric_data, buf.data, sizeof( numeric_data ) ), 0);

    simplebuffer_destroy( &buf );
}

void pack_simplebuffer_test_raw( void )
{
    simplebuffer buf;
    bool result;

    simplebuffer_init( &buf, NULL, 0 );

    result = pack_simplebuffer_raw( &buf, (unsigned char *)"TEST", 5 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_raw( &buf, (unsigned char *)"012345678901234567890123456789", 31 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_raw( &buf, (unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcde", 32 );
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_nil( &buf );
    BOOST_CHECK_EQUAL(result, true);
    
    BOOST_CHECK_EQUAL(buf.size, sizeof(raw_data));
    BOOST_CHECK_EQUAL(memcmp( buf.data, raw_data, sizeof(raw_data) ), 0);

    simplebuffer_destroy( &buf );
}

void pack_simplebuffer_test_raw32( void )
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
    BOOST_CHECK_EQUAL(result, true);
    result = pack_simplebuffer_nil( &buf );
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL( *(buf.data),     0xc2 );
    BOOST_CHECK_EQUAL( *((buf.data)+1), 0x00 );
    BOOST_CHECK_EQUAL( *((buf.data)+2), 0x02 );
    BOOST_CHECK_EQUAL( *((buf.data)+3), 0x00 );
    BOOST_CHECK_EQUAL( *((buf.data)+4), 0x00 );
    BOOST_CHECK_EQUAL( memcmp( test_data, (buf.data)+5, data_size ), 0 );
    BOOST_CHECK_EQUAL( *((buf.data)+5+data_size), 0xC0 );

    free(test_data);
    simplebuffer_destroy( &buf );
}

