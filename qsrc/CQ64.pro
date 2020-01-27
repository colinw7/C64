TEMPLATE = lib

TARGET = CQ64

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += \
-std=c++14 \

MOC_DIR = .moc

CONFIG += staticlib
CONFIG += c++14

SOURCES += \
CQ64.cpp \
CQ64_6502.cpp \
CQ64_VICII.cpp \

HEADERS += \
../qinclude/CQ64.h \
../qinclude/CQ64_6502.h \
../qinclude/CQ64_VICII.h \

DESTDIR     = ../lib
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. \
../qinclude \
../include \
../../C6502/include \
