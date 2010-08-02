#ifndef H_TEST_HPP_100802144935__
#define H_TEST_HPP_100802144935__

#include <gtest/gtest.h>

#include <float.h>

extern "C"
{
#include <pack.h>
#include <unpack.h>
#include <pack_simplebuffer.h>
#include <pack_simplebuffer_text.h>
#include <unpack_simplebuffer_text.h>
#include <simplebuffer.h>

#include "../serializer/defines.h"
}

class SimpleserializerTest : public ::testing::Test 
{
protected:
    virtual ~SimpleserializerTest() {
    }

    virtual void SetUp() {
        simplebuffer_system_init( 1024u,(uint8_t* (*)(size_t))malloc,(void (*)(void*))free );
    }
    

};
        

#endif //H_TEST_HPP_100802144935__
