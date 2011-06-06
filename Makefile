#############################################################################
# Makefile for building: soeditor
# Generated by qmake (2.01a) (Qt 4.7.3) on: ? 6? 6 19:54:11 2011
# Project:  soeditor.pro
# Template: app
# Command: /usr/local/Trolltech/Qt-4.7.3/bin/qmake -o Makefile soeditor.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/Trolltech/Qt-4.7.3/mkspecs/linux-g++-64 -I. -I/usr/local/Trolltech/Qt-4.7.3/include/QtCore -I/usr/local/Trolltech/Qt-4.7.3/include/QtGui -I/usr/local/Trolltech/Qt-4.7.3/include -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/Qt-4.7.3/lib
LIBS          = $(SUBLIBS)  -L/usr/local/Trolltech/Qt-4.7.3/lib -lQtGui -L/usr/local/Trolltech/Qt-4.7.3/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/local/Trolltech/Qt-4.7.3/bin/qmake
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

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		MainWindow.cpp \
		SOEKeyBind.cpp \
		sotextedit.cpp \
		Widget.cpp moc_soeditor.cpp
OBJECTS       = main.o \
		MainWindow.o \
		SOEKeyBind.o \
		sotextedit.o \
		Widget.o \
		moc_soeditor.o
DIST          = /usr/local/Trolltech/Qt-4.7.3/mkspecs/common/g++.conf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/linux.conf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/release.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/include_source_dir.prf \
		soeditor.pro
QMAKE_TARGET  = soeditor
DESTDIR       = 
TARGET        = soeditor

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
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: soeditor.pro  /usr/local/Trolltech/Qt-4.7.3/mkspecs/linux-g++-64/qmake.conf /usr/local/Trolltech/Qt-4.7.3/mkspecs/common/g++.conf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/linux.conf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/release.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/include_source_dir.prf \
		/usr/local/Trolltech/Qt-4.7.3/lib/libQtGui.prl \
		/usr/local/Trolltech/Qt-4.7.3/lib/libQtCore.prl
	$(QMAKE) -o Makefile soeditor.pro
/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/g++.conf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/unix.conf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/common/linux.conf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/qconfig.pri:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt_functions.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt_config.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/exclusive_builds.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/default_pre.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/release.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/default_post.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/warn_on.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/qt.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/unix/thread.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/moc.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/resources.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/uic.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/yacc.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/lex.prf:
/usr/local/Trolltech/Qt-4.7.3/mkspecs/features/include_source_dir.prf:
/usr/local/Trolltech/Qt-4.7.3/lib/libQtGui.prl:
/usr/local/Trolltech/Qt-4.7.3/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile soeditor.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/soeditor1.0.0 || $(MKDIR) .tmp/soeditor1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/soeditor1.0.0/ && $(COPY_FILE) --parents soeditor.h .tmp/soeditor1.0.0/ && $(COPY_FILE) --parents main.cpp MainWindow.cpp SOEKeyBind.cpp sotextedit.cpp Widget.cpp .tmp/soeditor1.0.0/ && (cd `dirname .tmp/soeditor1.0.0` && $(TAR) soeditor1.0.0.tar soeditor1.0.0 && $(COMPRESS) soeditor1.0.0.tar) && $(MOVE) `dirname .tmp/soeditor1.0.0`/soeditor1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/soeditor1.0.0


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

compiler_moc_header_make_all: moc_soeditor.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_soeditor.cpp
moc_soeditor.cpp: soeditor.h
	/usr/local/Trolltech/Qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) soeditor.h -o moc_soeditor.cpp

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

main.o: main.cpp soeditor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

MainWindow.o: MainWindow.cpp soeditor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow.o MainWindow.cpp

SOEKeyBind.o: SOEKeyBind.cpp soeditor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SOEKeyBind.o SOEKeyBind.cpp

sotextedit.o: sotextedit.cpp soeditor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sotextedit.o sotextedit.cpp

Widget.o: Widget.cpp soeditor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Widget.o Widget.cpp

moc_soeditor.o: moc_soeditor.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_soeditor.o moc_soeditor.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

