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

#ifndef __UNPACK_H_100629201544__
#define __UNPACK_H_100629201544__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef union unpack_base_value_t
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
} unpack_base_value_t;
    
typedef struct unpack_base_info_t
{
    size_t size;               ///< Serialized data size.
    uint8_t type;              ///< Data type.
    unpack_base_value_t value; ///< Data value.
} unpack_base_info_t;

unpack_base_info_t unpack_base( uint8_t* buf );

typedef struct unpack_raw_t
{
    size_t size;
    uint8_t* data;
} unpack_raw_t;

typedef union unpack_value_t
{
    bool bool_value;
    int int_value;
    unsigned int uint_value;
    float float_value;
#ifdef SUPPORT_64BIT_VALUE
    double double_value;
#endif
    unpack_raw_t raw_value;
} unpack_value_t;

typedef enum unpack_type_t
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
} unpack_type_t;

typedef struct unpack_info_t
{
    unpack_type_t type;       ///< データタイプ
    unpack_value_t value;     ///< 値
} unpack_info_t;

int unpack( unpack_info_t *info, uint8_t* buf );

#endif //__UNPACK_H_100629201544__
