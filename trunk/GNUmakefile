CC=gcc
CXX=g++

CFLAGS   += -Wall -O 
CXXFLAGS += $(CFLAGS)


CFLAGS   += -Isrc

# for BOOST
CFLAGS   += -I/usr/local/include/boost_1_43_0
CFLAGS   += -DBOOST_TEST_DYN_LINK
LDFLAGS  += -L/usr/local/lib/boost_1_43_0
LIBS     += -lboost_unit_test_framework

all: test.exe
OBJS += src/pack.o src/unpack.o
OBJS += tests/test_main.o
OBJS += tests/serialize_tests.o
OBJS += tests/simplebuffer_tests.o

test.exe : $(OBJS)
	g++ -o test.exe $(OBJS) $(LDFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -rf $(OBJS) test.exe