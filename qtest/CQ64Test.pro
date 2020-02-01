TEMPLATE = app

TARGET = CQ64Test

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += \
-std=c++14 \

MOC_DIR = .moc

SOURCES += \
CQ64.cpp \

HEADERS += \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH += \
. \
../include \
../../C64/qinclude \
../../C64/include \
../../C6502/include \

unix:LIBS += \
-L../lib \
-L../../C64/lib \
-L../../C6502/lib \
-lCQ64 -lC64 -lC6502 \
