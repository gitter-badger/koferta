! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}


TEMPLATE = lib
CONFIG  += dll staticlib
TARGET = common
VERSION  = 0

HEADERS += \
    LocalDatabase.h \
    functions.h \
    AbstractDatabase.h \
    PsqlDatabase.h \
    Database.h \
    Merchandise.h \
    SQLiteDatabase.h \
    Logger.h \
    MerchandiseSearchModel.h \
    MerchandiseSearch.h \
    CustomerSearch.h \
    OfferSearch.h

FORMS += \
    MerchandiseSearch.ui \
    CustomerSearch.ui \
    OfferSearch.ui
         
SOURCES += \
    LocalDatabase.cpp \
    functions.cpp \
    AbstractDatabase.cpp \
    PsqlDatabase.cpp \
    Database.cpp \
    Merchandise.cpp \
    SQLiteDatabase.cpp \
    Logger.cpp \
    MerchandiseSearchModel.cpp \
    MerchandiseSearch.cpp \
    CustomerSearch.cpp \
    OfferSearch.cpp
