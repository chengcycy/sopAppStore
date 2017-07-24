#-------------------------------------------------
#
# Project created by QtCreator 2017-04-16T10:25:05
#
#-------------------------------------------------
include(../syberos.pri)

QT       += dbus network
QT       -= gui

CONFIG += c++11

TARGET = sopstoreclinet
TEMPLATE = lib

DEFINES += SOPSTORECLINET_LIBRARY

QMAKE_LFLAGS += -Wl,-rpath=$$LIB_DIR -Wl,-Bsymbolic

SOURCES += sopstoreclinet.cpp \
    consttype.cpp

HEADERS += sopstoreclinet.h\
        sopstoreclinet_global.h \
    consttype.h

unix {
    target.path =  $$INSTALL_DIR/libs/
    INSTALLS += target
}
