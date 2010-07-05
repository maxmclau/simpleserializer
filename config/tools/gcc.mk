###################################################################################
# GCC用設定
# コマンド名
#
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
#
CC     :=gcc
CXX    :=g++
AS     :=$(CC) -x assembler-with-cpp
AR     :=$(GCC_PREFIX)ar
RANLIB :=$(GCC_PREFIX)ranlib

# デフォルト
ASFLAGS += -finput-charset=utf-8 -fexec-charset=utf-8
CFLAGS  += -finput-charset=utf-8 -fexec-charset=utf-8
CXXFLAGS += -Wall #-Wno-non-virtual-dtor
LDFLAGS +=

# コンパイル
define COMPILE_s
	@echo Compiling $<
	@$(AS) -c $(ASFLAGS)  $< -o $@
endef

define COMPILE_c
	@echo Compiling $<
	@$(CC)  -c $(CFLAGS) $< -o $@
endef

define COMPILE_m
	@echo Compiling $<
	@$(CC)  -c $(CFLAGS) $< -o $@
endef

define COMPILE_cxx
	@echo Compiling $<
	@$(CXX)  -c $(CFLAGS) $(CXXFLAGS) $< -o $@
endef

ifneq ($(strip $(filter %.m, $(SOURCES))),)
	LIBRARIES += -lobjc
endif

# リンク

# リンカとしてg++を利用する。
define LINK_objs
	@echo Linking CXX
	@$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS) $(LIBRARIES)
endef
# C++が無ければ、リンカとしてgccを利用する。
ifeq ($(strip $(filter %$(CXXEXT), $(SOURCES))),)
define LINK_objs
	@echo Linking C
	@$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS) $(LIBRARIES)
endef
endif

define ARCHIVE_objs
	@echo Archiving
	@$(AR) r $@ $(OBJECTS)
	@$(RANLIB) $@
endef

debug: gcc-debug

.PHONY: gcc-debug
gcc-debug:
	@echo 'GCC Options'
	@echo 'ASFLAGS             :' $(ASFLAGS)
	@echo 'CFLAGS              :' $(CFLAGS)
	@echo 'CXXFLAGS            :' $(CXXFLAGS)
	@echo 'LDFLAGS             :' $(LDFLAGS)
	@echo 'AUTO_GENERATED_FILES:' $(AUTO_GENERATED_FILES)
