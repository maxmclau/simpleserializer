#ifndef __UNPACK_H_100629201544__
#define __UNPACK_H_100629201544__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef union unpack_value_t
{
    int8_t int8_value;
    uint8_t uint8_value;
    int16_t int16_value;
    uint16_t uint16_value;
    int32_t int32_value;
    uint32_t uint32_value;
    float float_value;
#ifdef SUPPORT_64BIT_VALUE
    int64_t int64_value;
    uint64_t uint64_value;
    double double_value;
#endif
    size_t size;
    uint8_t* raw_data;
} unpack_value_t;
    
typedef struct unpack_info_t
{
    size_t size;              ///< Serialized data size.
    uint8_t type;             ///< Data type.
    unpack_value_t value;     ///< Data value.
} unpack_info_t;

unpack_info_t unpack( uint8_t* buf );


typedef struct unpack_raw_t
{
    size_t size;
    uint8_t* data;
} unpack_raw_t;

typedef union unpack_ex_value_t
{
    bool bool_value;
    int int_value;
    unsigned int uint_value;
    float float_value;
#ifdef SUPPORT_64BIT_VALUE
    double double_value;
#endif
    unpack_raw_t raw_value;
} unpack_ex_value_t;

typedef enum unpack_ex_type_t
{
    UNPACK_TYPE_NIL,
    UNPACK_TYPE_BOOL,
    UNPACK_TYPE_INT,
    UNPACK_TYPE_UINT,
    UNPACK_TYPE_FLOAT,
#ifdef SUPPORT_64BIT_VALUE
    UNPACK_TYPE_DOUBLE,
#endif
    UNPACK_TYPE_RAW
} unpack_ex_type_t;

typedef struct unpack_ex_info_t
{
    unpack_ex_type_t type;       ///< データタイプ
    unpack_ex_value_t value;     ///< 値
} unpack_ex_info_t;

int unpack_ex( unpack_ex_info_t *info_ex, uint8_t* buf );

#endif //__UNPACK_H_100629201544__
