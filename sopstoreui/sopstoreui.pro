#-------------------------------------------------
#
# Project generated by QtCreator for SyberOS.
#
#-------------------------------------------------

# This is needed for using syberos-application module
include(../syberos.pri)

QT += gui qml quick network dbus
TARGET = sopstoreui
TEMPLATE = app

CONFIG += link_pkgconfig qml_debug c++11
PKGCONFIG += syberos-application syberos-application-cache
PKGCONFIG += syberos-qt
PKGCONFIG += syberos-qt-system

QMAKE_LFLAGS += -Wl,-rpath=$$LIB_DIR -Wl,-Bsymbolic

#qml.qrc
RESOURCES +=  images.qrc \
    js.qrc \
    newui.qrc

HEADERS += src/sopstoreui_workspace.h

SOURCES += src/main.cpp \
		   src/sopstoreui_workspace.cpp

OTHER_FILES += qml/*.qml

target.path = $$INSTALL_DIR/bin

res.files = logo
res.path = $$INSTALL_DIR/

#h5app.files = h5
#h5app.path = $$INSTALL_DIR/bin

INSTALLS += target res

DISTFILES += \
    js/Helper.js \
    qml/apps/AppsMain.qml \
    qml/component/TabviewStyle.qml \
    qml/contacts/ContactMain.qml \
    qml/me/MeMain.qml \
    qml/notice/NoticeMain.qml \
    qml/me/Login.qml \
    qml/MainClient.qml \
    qml/component/TitleBar.qml \
    qml/apps/SlidesshowIndicator.qml

unix:!macx: LIBS += -L$$OUT_PWD/../sopstoreclinet/ -lsopstoreclinet

INCLUDEPATH += $$PWD/../sopstoreclinet
DEPENDPATH += $$PWD/../sopstoreclinet
