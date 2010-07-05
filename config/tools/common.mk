######################################################################
#
# GNUmakefile for "GNU Make 3.81"
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
######################################################################
GNUMAKEFILE_VERSION := ' $$Revision: 58 $$ '

######################################################################
# Common settings.
# Delete default rule.
.SUFFIXES:

######################################################################
# External tools.

MKDIR=/bin/mkdir
CAT=  /bin/cat
RM=   /bin/rm


######################################################################
# Default build target.
.DEFAULT_GOAL := all
.PHONY: all
all: outdirs premake target postmake

######################################################################
# File name settings.

# C++ file extension.
CXXEXT=.cpp

# Assembler file extension.
ASMEXT=.S

# File extension use as source code.
SRCEXTS=$(ASMEXT) .c .m $(CXXEXT)

# Object file extension.
OBJEXT=.o

# Pre make target.
.PHONY: premake
premake:

# Post make target.
.PHONY: postmake
postmake:

######################################################################
# Output files.

# Default name.
NAME=$(notdir $(abspath .))
ifeq ($(strip $(NAME)),)
	NAME=root
endif

# If OUTDIR is not set use $(NAME)_Data
ifeq ($(strip $(OUTDIR)),)
	OUTDIR=$(NAME)_Data
endif


# If OBJDIR is not set use default value.
ifeq ($(strip $(OBJDIR)),)
# Repeat 'obj', same as number of '..'.
	comma:=,
	empty:=
	space:=$(empty) $(empty)
	OBJDIR:=Objects$(subst $(space),/, \
		$(strip \
		$(subst ..,obj, \
		$(filter .., \
		$(subst /,$(space),$(firstword $(sort $(filter-out . .., $(SRCDIRS)))))))))
endif

######################################################################
# Source files.

# Search source files in SRCDIRS, except filename that SOURCE_EXCEPTION has.
SOURCES := $(filter-out $(SOURCE_EXCEPTION), \
	$(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS)))))

# Add extra source directly.
ifneq ($(strip $(SOURCE_EXTRA)),)
	SOURCES+=$(SOURCE_EXTRA)
endif


######################################################################
# Generate objects.

OBJECTS=$(addprefix $(OUTDIR)/$(OBJDIR)/, \
		$(addsuffix $(OBJEXT), \
		$(basename $(sort $(SOURCES)))))

# 依存関係ファイルリスト
DEPENDS=$(OBJECTS:$(OBJEXT)=.d)

# if ARCHIVE was set use it as library name.
# if ARCHIVE was not set use PROGRAM as executable name.
# if neither PROGRAM nor ARCHIVE was not set use current directory name as executable name.
ifeq ($(strip $(ARCHIVE)),)
ifeq ($(strip $(PROGRAM)),)
PROGRAM=$(OUTDIR)/$(NAME)
endif
TARGET=$(PROGRAM)
else
TARGET=$(ARCHIVE)
endif

.PHONY: target
target: $(TARGET)

$(TARGET) : $(OBJECTS) $(LIBS)
ifeq ($(strip $(ARCHIVE)),)
	$(LINK_objs)
else
	$(ARCHIVE_objs)
endif


# Create output directory.
OUTDIRS=$(sort $(dir $(OBJECTS))) $(dir $(TARGET))
.PHONY: outdirs
outdirs: $(OUTDIRS)
$(OUTDIRS):
	@$(MKDIR) -p $@

# Include dependencies if they exist.
-include $(DEPENDS)

######################################################################
# Compile rules.

# Assembler
$(OUTDIR)/$(OBJDIR)/%$(OBJEXT):%$(ASMEXT)
	$(COMPILE_s)
	$(CHECK_s)
# C
$(OUTDIR)/$(OBJDIR)/%$(OBJEXT):%.c
	$(COMPILE_c)
	$(CHECK_c)

# ObjC
$(OUTDIR)/$(OBJDIR)/%$(OBJEXT):%.m
	$(COMPILE_m)
	$(CHECK_m)
# C++
$(OUTDIR)/$(OBJDIR)/%$(OBJEXT):%$(CXXEXT)
	$(COMPILE_cxx)
	$(CHECK_cxx)

######################################################################
# Clean
.PHONY: clean
clean:
	@$(RM) -f $(OBJECTS)
	@$(RM) -f $(TARGET).exe
	@$(RM) -f $(TARGET)

.PHONY: all-clean
all-clean: clean
	@$(RM) -rf $(OUTDIR)

.PHONY: lib-clean lib-all-clean
lib-all-clean:
lib-clean:


######################################################################
# Debug target
.PHONY: debug
debug:
	@echo 'SRCDIRS             :' $(SRCDIRS)
	@echo 'SOURCES             :' $(SOURCES)
	@echo 'OBJECTS             :' $(OBJECTS)
	@echo 'DEPENDS             :' $(DEPENDS)
	@echo "FIND_EXCEPTION      :" $(FIND_EXCEPTION)
	@echo "TARGET              :" $(TARGET)
	@echo "OUTDIR              :" $(OUTDIR)
	@echo 'OBJDIR              :' $(OBJDIR)
	@echo "GNUMAKEFILE_VERSION :" $(GNUMAKEFILE_VERSION)

######################################################################
# Help target
.PHONY: help
help:
	@echo "Generic GNUmakefile " $(GNUMAKEFILE_VERSION)
	@echo "TARGETS:"
	@echo "	all		Generate binary.(executable or library)"
	@echo "	debug		Display make variables."
	@echo "	clean		Delete object files and binaries."
	@echo "	all-clean	Delete output directory completely."
	@echo "	help		Display this message."

######################################################################
# No source was found on SRCDIRS.
ifeq ($(strip $(SOURCES)),)
ifneq ($(if $(or $(findstring debug,$(MAKECMDGOALS)), \
                 $(findstring help,$(MAKECMDGOALS))),1),1)
	$(error Cannot find source code.)
endif
endif

######################################################################
