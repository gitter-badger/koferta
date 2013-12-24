! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}

TARGET = ../kOferta

TEMPLATE = app

QT += printsupport


unix {
LIBS += -L../common -lcommon
}

win32 {
LIBS += -L../common/debug -lcommon
}

HEADERS += \
    MainWindow.h \
    MerchendiseSelectionDelegate.h \
    MerchandiseListModel.h \
    MerchandiseListDelegate.h \
    MerchandiseSelectionModel.h \
    MerchandiseSelection.h \
    CustomerSelection.h \
    OfferSelection.h

FORMS += \
    MainWindow.ui \
    OfferSelection.ui \
    CustomerSelection.ui
         
SOURCES += \
    MainWindow.cpp \
    MerchendiseSelectionDelegate.cpp \
    MerchandiseListModel.cpp \
    MerchandiseListDelegate.cpp \
    MerchandiseSelectionModel.cpp \
    MerchandiseSelection.cpp \
    CustomerSelection.cpp \
    main.cpp \
    OfferSelection.cpp

