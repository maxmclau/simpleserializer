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
# 全体設定
# デフォルトルールを消去
.SUFFIXES:

######################################################################
# 外部ツール

MKDIR=/bin/mkdir
CAT=  /bin/cat
RM=   /bin/rm


######################################################################
# ビルド
.DEFAULT_GOAL := all
.PHONY: all
all: outdirs premake target postmake

######################################################################
# ファイル名関連


# C++の拡張子に関しては諸説あるので変数としておく。
# ただし、複数の拡張子が混在する可能性については考えない
CXXEXT=.cpp

# アセンブリ言語の拡張子に関しても同様
ASMEXT=.S

# ソースコードとして取り扱う拡張子
SRCEXTS=$(ASMEXT) .c .m $(CXXEXT)

# オブジェクトファイルの拡張子
OBJEXT=.o

# ディレクトリ自動探索から除外するディレクトリ名
DIR_EXCEPTION=CVS .svn $(notdir $(OUTDIR)) $(notdir $(OBJDIR))

# ビルドする前に実行されるターゲット
.PHONY: premake
premake:

# ビルドした後に実行されるターゲット
.PHONY: postmake
postmake:

######################################################################
# 出力ファイル等
# デフォルト出力名
NAME=$(notdir $(abspath .))
ifeq ($(strip $(NAME)),)
	NAME=root
endif

# 出力ディレクトリが指定されていなかった場合にはディレクトリ名_Dataに出力する
ifeq ($(strip $(OUTDIR)),)
	OUTDIR=$(NAME)_Data
endif


# オブジェクト出力ディレクトリが指定されていなかった場合はデフォルト値を使用する
ifeq ($(strip $(OBJDIR)),)
# '..' の数だけ'obj'を重ねる処理
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
# ソースファイル

# SOURCE_EXCEPTIONに含まれるファイルを除外しながら、SRCDIRSに含まれるソースコードを探索する。
SOURCES := $(filter-out $(SOURCE_EXCEPTION), \
	$(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS)))))

# 検索対象にならないファイルを追加する。
ifneq ($(strip $(SOURCE_EXTRA)),)
	SOURCES+=$(SOURCE_EXTRA)
endif


######################################################################
# 生成物
# オブジェクトファイルリスト
OBJECTS=$(addprefix $(OUTDIR)/$(OBJDIR)/, \
		$(addsuffix $(OBJEXT), \
		$(basename $(sort $(SOURCES)))))

# 依存関係ファイルリスト
DEPENDS=$(OBJECTS:$(OBJEXT)=.d)

# ARCHIVEが指定されていたらライブラリ生成ターゲットとして指定
# ARCHIVEが指定されていない場合、PROGRAMを実行ファイル生成ターゲットとする。
# PROGRAMも指定されていない場合には、カレントディレクトリ名を実行ファイル名とする
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


# 出力用ディレクトリ作成
OUTDIRS=$(sort $(dir $(OBJECTS))) $(dir $(TARGET))
.PHONY: outdirs
outdirs: $(OUTDIRS)
$(OUTDIRS):
	@$(MKDIR) -p $@

# 依存関係ファイルが存在したらincludeする
-include $(DEPENDS)

######################################################################
# コンパイル
# 個別ルール

# アセンブラ
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
# クリーン
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
# このメイクファイルのデバッグ用
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
# ヘルプ
.PHONY: help
help:
	@echo "汎用GNUmakefile " $(GNUMAKEFILE_VERSION)
	@echo "TARGETS:"
	@echo "	all		バイナリを生成します"
	@echo "	debug		各種変数を表示します"
	@echo "	clean		オブジェクト、バイナリを削除します"
	@echo "	all-clean	出力ディレクトリを完全に削除します"
	@echo "	help		このメッセージを表示"

######################################################################
# エラー

# ソースコードが見つからない
ifeq ($(strip $(SOURCES)),)
ifneq ($(if $(or $(findstring debug,$(MAKECMDGOALS)), \
                 $(findstring help,$(MAKECMDGOALS))),1),1)
	$(error Cannot find source code.)
endif
endif

######################################################################
