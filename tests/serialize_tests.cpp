#include <boost/test/unit_test.hpp>
#include <float.h>

using boost::unit_test_framework::test_suite;

extern "C"
{
#include "pack.h"
#include "unpack.h"

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

void pack_test_numeric( void )
{
    int size1 = 0;
    unsigned char buf1[1024];
    int size2 = 0;
    unsigned char buf2[1024];

    size1 += pack_nil( &(buf1[size1]) );
    size1 += pack_bool( &(buf1[size1]), false );
    size1 += pack_bool( &(buf1[size1]), true );
    size1 += pack_float( &(buf1[size1]), FLT_MAX/2 );
    size1 += pack_float( &(buf1[size1]), FLT_MIN/2 );
#ifdef SUPPORT_64BIT_VALUE
    size1 += pack_double( &(buf1[size1]), FLT_MAX*2 );
    size1 += pack_double( &(buf1[size1]), FLT_MIN*2 );
#endif
    size1 += pack_fixuint( &(buf1[size1]), 0 );
    size1 += pack_fixuint( &(buf1[size1]), 127 );
    size1 += pack_uint8( &(buf1[size1]), 128 );
    size1 += pack_uint8( &(buf1[size1]), 255 );
    size1 += pack_uint16( &(buf1[size1]), 256 );
    size1 += pack_uint16( &(buf1[size1]), 65535 );
    size1 += pack_uint32( &(buf1[size1]), 65536 );
    size1 += pack_uint32( &(buf1[size1]), 268435455 );
    size1 += pack_fixint( &(buf1[size1]), -1 );
    size1 += pack_fixint( &(buf1[size1]), -32 );
    size1 += pack_int8( &(buf1[size1]), -33 );
    size1 += pack_int8( &(buf1[size1]), -128 );
    size1 += pack_int16( &(buf1[size1]), -129 );
    size1 += pack_int16( &(buf1[size1]), -32768 );
    size1 += pack_int32( &(buf1[size1]), -32769 );
    size1 += pack_int32( &(buf1[size1]), -134217728 );

    size2 += pack_nil( &(buf2[size2]) );
    size2 += pack_bool( &(buf2[size2]), false );
    size2 += pack_bool( &(buf2[size2]), true );
    size2 += pack_float( &(buf2[size2]), FLT_MAX/2 );
    size2 += pack_float( &(buf2[size2]), FLT_MIN/2 );
#ifdef SUPPORT_64BIT_VALUE
    size2 += pack_double( &(buf2[size2]), FLT_MAX*2 );
    size2 += pack_double( &(buf2[size2]), FLT_MIN*2 );
#endif
    size2 += pack_int( &(buf2[size2]), 0 );
    size2 += pack_int( &(buf2[size2]), 127 );
    size2 += pack_int( &(buf2[size2]), 128 );
    size2 += pack_int( &(buf2[size2]), 255 );
    size2 += pack_int( &(buf2[size2]), 256 );
    size2 += pack_int( &(buf2[size2]), 65535 );
    size2 += pack_int( &(buf2[size2]), 65536 );
    size2 += pack_int( &(buf2[size2]), 268435455 );
    size2 += pack_int( &(buf2[size2]), -1 );
    size2 += pack_int( &(buf2[size2]), -32 );
    size2 += pack_int( &(buf2[size2]), -33 );
    size2 += pack_int( &(buf2[size2]), -128 );
    size2 += pack_int( &(buf2[size2]), -129 );
    size2 += pack_int( &(buf2[size2]), -32768 );
    size2 += pack_int( &(buf2[size2]), -32769 );
    size2 += pack_int( &(buf2[size2]), -134217728 );

    BOOST_CHECK_EQUAL(size1, size2);
    BOOST_CHECK_EQUAL((size_t)size1, sizeof( numeric_data) );
    BOOST_CHECK_EQUAL(memcmp( numeric_data, buf1, size1 ), 0 );
    BOOST_CHECK_EQUAL(memcmp( numeric_data, buf2, size2 ), 0 );
    BOOST_CHECK_EQUAL(memcmp( buf1, buf2, size1 ), 0 );
}

void unpack_base_test_numeric( void )
{
    size_t pos = 0;
    unpack_base_info_t info;
    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_NIL );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_FALSE );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_TRUE );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_FLOAT );
    BOOST_CHECK_EQUAL( info.value.float_value, FLT_MAX/2 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_FLOAT );
    BOOST_CHECK_EQUAL( info.value.float_value, FLT_MIN/2 );
    pos += info.size;

#ifdef SUPPORT_64BIT_VALUE
    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_DOUBLE );
    BOOST_CHECK_EQUAL( info.value.double_value, FLT_MAX*2 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_DOUBLE );
    BOOST_CHECK_EQUAL( info.value.double_value, FLT_MIN*2 );
    pos += info.size;
#endif
    
    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_POSITIVE_FIXNUM );
    BOOST_CHECK_EQUAL( info.value.uint8_value, 0 );
    pos += info.size;
    
    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_POSITIVE_FIXNUM );
    BOOST_CHECK_EQUAL( info.value.uint8_value, 127 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_UINT8 );
    BOOST_CHECK_EQUAL( info.value.uint8_value, 128 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_UINT8 );
    BOOST_CHECK_EQUAL( info.value.uint8_value, 255 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_UINT16 );
    BOOST_CHECK_EQUAL( info.value.uint16_value, 256 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_UINT16 );
    BOOST_CHECK_EQUAL( info.value.uint16_value, 65535 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_UINT32 );
    BOOST_CHECK_EQUAL( info.value.uint32_value, 65536u );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_UINT32 );
    BOOST_CHECK_EQUAL( info.value.uint32_value, 268435455u );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_NEGATIVE_FIXNUM );
    BOOST_CHECK_EQUAL( info.value.int8_value, -1 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_NEGATIVE_FIXNUM );
    BOOST_CHECK_EQUAL( info.value.int8_value, -32 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_INT8 );
    BOOST_CHECK_EQUAL( info.value.int8_value, -33 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_INT8 );
    BOOST_CHECK_EQUAL( info.value.int8_value, -128 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_INT16 );
    BOOST_CHECK_EQUAL( info.value.int16_value, -129 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_INT16 );
    BOOST_CHECK_EQUAL( info.value.int16_value, -32768 );
    pos += info.size;

    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_INT32 );
    BOOST_CHECK_EQUAL( info.value.int32_value, -32769 );
    pos += info.size;
    
    info = unpack_base( (unsigned char *)&(numeric_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_INT32 );
    BOOST_CHECK_EQUAL( info.value.int32_value, -134217728 );
    pos += info.size;
    
}

void pack_test_raw( void )
{
    int size = 0;
    unsigned char buf[1024];

    size += pack_raw( &(buf[size]), (unsigned char *)"TEST", 5 );
    size += pack_raw( &(buf[size]), (unsigned char *)"012345678901234567890123456789", 31 );
    size += pack_raw( &(buf[size]), (unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcde", 32 );
    size += pack_nil( &(buf[size]) );
    
    BOOST_CHECK_EQUAL( (size_t)size, sizeof(raw_data) );
    BOOST_CHECK_EQUAL( memcmp( buf, raw_data, size ), 0 );
}

void unpack_base_test_raw( void )
{
    size_t pos = 0;
    unpack_base_info_t info;

    info = unpack_base( (unsigned char *)&(raw_data[pos]) );
    pos += info.size;
    BOOST_CHECK_EQUAL( info.type, TYPE_FIXROW );
    BOOST_CHECK_EQUAL( info.value.size, 5u );
    BOOST_CHECK_EQUAL( strcmp( "TEST", (char *)&(raw_data[pos]) ), 0 );
    pos += info.value.size;

    info = unpack_base( (unsigned char *)&(raw_data[pos]) );
    pos += info.size;
    BOOST_CHECK_EQUAL( info.type, TYPE_FIXROW );
    BOOST_CHECK_EQUAL( info.value.size, 31u );
    BOOST_CHECK_EQUAL( strcmp( "012345678901234567890123456789", (char *)&(raw_data[pos]) ), 0 );
    pos += info.value.size;

    info = unpack_base( (unsigned char *)&(raw_data[pos]) );
    pos += info.size;
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_RAW16 );
    BOOST_CHECK_EQUAL( info.value.size, 32u );
    BOOST_CHECK_EQUAL( strcmp( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde", (char *)&(raw_data[pos]) ), 0 );
    pos += info.value.size;

    info = unpack_base( (unsigned char *)&(raw_data[pos]) );
    BOOST_CHECK_EQUAL( info.type, TYPE_VALIABLE_NIL );
    pos += info.size;

}

void pack_test_raw32( void )
{
    int i = 0, data_size = 131072, size = 0;
    unsigned char *test_data = (unsigned char *)malloc( data_size );
    unsigned char *buf = (unsigned char *)malloc( data_size + 10 );

    for( i = 0; i < data_size; i++ )
    {
        *(test_data+i) = i & 0xff;
    }
    
    size += pack_raw( &(buf[size]), test_data, data_size );
    size += pack_nil( &(buf[size]));
    BOOST_CHECK_EQUAL( *buf,     0xc2 );
    BOOST_CHECK_EQUAL( *(buf+1), 0x00 );
    BOOST_CHECK_EQUAL( *(buf+2), 0x02 );
    BOOST_CHECK_EQUAL( *(buf+3), 0x00 );
    BOOST_CHECK_EQUAL( *(buf+4), 0x00 );
    BOOST_CHECK_EQUAL( memcmp( test_data, buf+5, data_size ), 0 );
    BOOST_CHECK_EQUAL( *(buf+5+data_size), 0xC0 );
    
    free(test_data);
    free(buf);
}

void unpack_test( void )
{
    unpack_info_t info;
    int size = 0;
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_NIL );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_BOOL );
    BOOST_CHECK_EQUAL( info.value.bool_value, false );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_BOOL );
    BOOST_CHECK_EQUAL( info.value.bool_value, true );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
#ifdef SUPPORT_64BIT_VALUE
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
#endif
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 0u );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 127u );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 128u );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 255u );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 256u );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 65535u );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 65536u );
    
    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_UINT );
    BOOST_CHECK_EQUAL( info.value.uint_value, 268435455u );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -1 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -32 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -33 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -128 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -129 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -32768 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -32769 );

    size += unpack( &info, (unsigned char *)&(numeric_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_INT );
    BOOST_CHECK_EQUAL( info.value.int_value, -134217728 );

    size = 0;
    size += unpack( &info, (unsigned char *)&(raw_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_RAW );
    BOOST_CHECK_EQUAL( info.value.raw_value.size, 5u );
    BOOST_CHECK_EQUAL( strcmp("TEST", (char *)info.value.raw_value.data), 0 );

    size += unpack( &info, (unsigned char *)&(raw_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_RAW );
    BOOST_CHECK_EQUAL( info.value.raw_value.size, 31u );
    BOOST_CHECK_EQUAL( strcmp("012345678901234567890123456789", (char *)info.value.raw_value.data), 0 );

    size += unpack( &info, (unsigned char *)&(raw_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_RAW );
    BOOST_CHECK_EQUAL( info.value.raw_value.size, 32u );
    BOOST_CHECK_EQUAL( strcmp("ABCDEFGHIJKLMNOPQRSTUVWXYZabcde", (char *)info.value.raw_value.data), 0 );
}

void unpack_test_raw32( void )
{
    unpack_info_t info;
    int i = 0, size = 0, data_size = 131072;
    unsigned char *test_data = (unsigned char *)malloc( data_size + 10 );

    *test_data = 0xc2;
    *(test_data+1) = 0x00;
    *(test_data+2) = 0x02;
    *(test_data+3) = 0x00;
    *(test_data+4) = 0x00;
    for( i = 0; i < data_size; i++ )
    {
        *(test_data+i+5) = i & 0xff;
    }
    *(test_data+i+5) = 0xc0;
    
    size += unpack( &info, (unsigned char *)&(test_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_RAW );
    BOOST_CHECK_EQUAL( info.value.raw_value.size, (size_t)data_size );
    BOOST_CHECK_EQUAL( memcmp( test_data+5, info.value.raw_value.data, data_size), 0 );

    size += unpack( &info, (unsigned char *)&(test_data[size]) );
    BOOST_CHECK_EQUAL( info.type, UNPACK_TYPE_NIL );
    
    free(test_data);
}

