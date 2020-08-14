APPL_ASMOBJS :=

SRCLANG := c++
DUMMY := $(echo "**debug**")

# ev3 のビルド処理の概要
#１．Makeコマンド実行時の作業ディレクトリを得る
#２．Makefile.workspace を読み込み
#３．APPLDIR/Makefile.inc を読み込み
#４．img: のルールを定義
#５．prepare-object ルールを実行 ⇒ ビルド用のMakefileを生成
#６．OBJDIRへcd 
#７．５のMakefileでmake clean 
#８．５のMakefileを実行

# ../common/Makefile.workspace の５２行目の ifeqの判定がおかしいため、
# ../workspace/アプリ/Makefile.img が読み込まれない。下記は、読み込ませるための暫定処置。
# なお、Makefile.img はサブディレクトリ以下のソースをビルド対象に含むためのルールを追加している。
MKFILE_DIR := $(APPLDIR)

ifdef APPLDIR
	# サブディレクトリの cfgファイルを抽出
	_APPCFGS := $(shell find $(APPLDIR) ! -name app.cfg -name *.cfg -printf '%P ')

	# cfgファイルのリストを作成
	_DUMMY := $(shell echo > $(APPLDIR)/subapp.list)
	_DUMMY := $(foreach item, $(_APPCFGS), $(shell echo 'INCLUDE("'$(item)'");' >> $(APPLDIR)/subapp.list))
endif

# 上記ビルド処理概要の「８」では APPLDIR 未定義になっている
ifdef APPLDIRS
	APPLDIR := $(firstword $(APPLDIRS))
endif

# サブディレクトリのソースファイルを抽出する
_CXXSRCS := $(shell find $(APPLDIR) ! -name app.cpp -name \*.cpp -printf '%P ')
_CSRCS   := $(shell find $(APPLDIR) ! -name app.c   -name \*.c   -printf '%P ')
_CXXOBJS := $(_CXXSRCS:%.cpp=%.o)
_COBJS   := $(_CSRCS:%.c=%.o)


ifdef USE_CXX
	APPL_CXXOBJS += $(_CXXOBJS)
	APPL_COBJS   += $(_COBJS)
else
	APPL_COBJS += $(_COBJS)
endif

