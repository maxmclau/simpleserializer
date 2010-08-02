#  Copyright (c) 2010  Yukio Obuchi
# 
#   Permission is hereby granted, free of charge, to any person
#  obtaining a copy of this software and associated documentation files
#  (the "Software"), to deal in the Software without restriction,
#  including without limitation the rights to use, copy, modify, merge,
#  publish, distribute, sublicense, and/or sell copies of the Software,
#  and to permit persons to whom the Software is furnished to do so,
#  subject to the following conditions:
# 
#   The above copyright notice and this permission notice shall be
#  included in all copies or substantial portions of the Software.
# 
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
#  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
#  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
#  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
PROJ_ROOT = .
TOOLDIR = $(PROJ_ROOT)/build/tools


CFLAGS   += -DSUPPORT_64BIT_VALUE
CFLAGS   += -Werror -g -Wall -O 
CXXFLAGS += $(CFLAGS)

CFLAGS   += -I$(PROJ_ROOT)/include

# for google test
CFLAGS   += $(shell gtest-config --cxxflags)
LIBRARIES  += $(shell gtest-config --ldflags) $(shell gtest-config --libs)

SRCDIRS += $(PROJ_ROOT)/src/serializer
SRCDIRS += $(PROJ_ROOT)/src/tests

include $(TOOLDIR)/common.mk
include $(TOOLDIR)/gcc.mk

#LOG_LEVEL:=all
LOG_LEVEL:=error

.PHONY:run-test
run-test: all
	@$(TARGET)
