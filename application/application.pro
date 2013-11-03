! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}

TARGET = ../kOferta

TEMPLATE = app

QT += printsupport

LIBS += -L../common -lcommon

HEADERS += \
    LoadDialog.h \
    MainWindow.h \
    WyborKlienta.h \
    WyborTowaru.h \
    TowarModel.h \
    TowarDelegate.h \
    WyborTowaruModel.h \
    MerchendiseSelectionDelegate.h

FORMS += \
    LoadDialog.ui \
    MainWindow.ui \
    WyborKlienta.ui
         
SOURCES += \
    LoadDialog.cpp \
    Main.cpp \
    MainWindow.cpp \
    WyborKlienta.cpp \
    WyborTowaru.cpp \
    TowarModel.cpp \
    TowarDelegate.cpp \
    WyborTowaruModel.cpp \
    MerchendiseSelectionDelegate.cpp

