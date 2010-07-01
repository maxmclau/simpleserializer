CC=gcc
CXX=g++

CFLAGS   += -Wall -O 
CXXFLAGS += $(CFLAGS)


CFLAGS   += -I/usr/local/include/boost_1_43_0
CFLAGS   += -DBOOST_TEST_MAIN
CFLAGS   += -DBOOST_TEST_DYN_LINK
LDFLAGS  += -L/usr/local/lib/boost_1_43_0
LIBS     += -lboost_unit_test_framework


all: test.exe
OBJS = src/pack.o src/unpack.o src/TEST_serialize.o

test.exe : $(OBJS)
	g++ -o test.exe $(OBJS) $(LDFLAGS) $(LIBS)


.PHONY: clean
clean:
	rm -rf $(OBJS) test.exe