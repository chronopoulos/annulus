#############################################################################
# Makefile for building: bin/annulus
# Generated by qmake (2.01a) (Qt 4.8.6) on: Tue Jul 28 18:45:03 2015
# Project:  annulus.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile annulus.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -Iinclude -Ibuild
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lsndfile -lasound -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/

####### Files

SOURCES       = src/main.cpp \
		src/MainWindow.cpp \
		src/Looper.cpp \
		src/AudioThread.cpp \
		src/PlayPauseButton.cpp \
		src/Annulus.cpp build/moc_MainWindow.cpp \
		build/moc_Looper.cpp \
		build/moc_AudioThread.cpp \
		build/moc_PlayPauseButton.cpp
OBJECTS       = build/main.o \
		build/MainWindow.o \
		build/Looper.o \
		build/AudioThread.o \
		build/PlayPauseButton.o \
		build/Annulus.o \
		build/moc_MainWindow.o \
		build/moc_Looper.o \
		build/moc_AudioThread.o \
		build/moc_PlayPauseButton.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		annulus.pro
QMAKE_TARGET  = annulus
DESTDIR       = bin/
TARGET        = bin/annulus

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/ || $(MKDIR) bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: annulus.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile annulus.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile annulus.pro

dist: 
	@$(CHK_DIR_EXISTS) build/annulus1.0.0 || $(MKDIR) build/annulus1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/annulus1.0.0/ && $(COPY_FILE) --parents include/MainWindow.h include/Looper.h include/AudioThread.h include/PlayPauseButton.h include/Annulus.h build/annulus1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/MainWindow.cpp src/Looper.cpp src/AudioThread.cpp src/PlayPauseButton.cpp src/Annulus.cpp build/annulus1.0.0/ && (cd `dirname build/annulus1.0.0` && $(TAR) annulus1.0.0.tar annulus1.0.0 && $(COMPRESS) annulus1.0.0.tar) && $(MOVE) `dirname build/annulus1.0.0`/annulus1.0.0.tar.gz . && $(DEL_FILE) -r build/annulus1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: build/moc_MainWindow.cpp build/moc_Looper.cpp build/moc_AudioThread.cpp build/moc_PlayPauseButton.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) build/moc_MainWindow.cpp build/moc_Looper.cpp build/moc_AudioThread.cpp build/moc_PlayPauseButton.cpp
build/moc_MainWindow.cpp: include/MainWindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) include/MainWindow.h -o build/moc_MainWindow.cpp

build/moc_Looper.cpp: include/Looper.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) include/Looper.h -o build/moc_Looper.cpp

build/moc_AudioThread.cpp: include/Looper.h \
		include/AudioThread.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) include/AudioThread.h -o build/moc_AudioThread.cpp

build/moc_PlayPauseButton.cpp: include/PlayPauseButton.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) include/PlayPauseButton.h -o build/moc_PlayPauseButton.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

build/main.o: src/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/main.o src/main.cpp

build/MainWindow.o: src/MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/MainWindow.o src/MainWindow.cpp

build/Looper.o: src/Looper.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Looper.o src/Looper.cpp

build/AudioThread.o: src/AudioThread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/AudioThread.o src/AudioThread.cpp

build/PlayPauseButton.o: src/PlayPauseButton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/PlayPauseButton.o src/PlayPauseButton.cpp

build/Annulus.o: src/Annulus.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Annulus.o src/Annulus.cpp

build/moc_MainWindow.o: build/moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_MainWindow.o build/moc_MainWindow.cpp

build/moc_Looper.o: build/moc_Looper.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Looper.o build/moc_Looper.cpp

build/moc_AudioThread.o: build/moc_AudioThread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_AudioThread.o build/moc_AudioThread.cpp

build/moc_PlayPauseButton.o: build/moc_PlayPauseButton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_PlayPauseButton.o build/moc_PlayPauseButton.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

