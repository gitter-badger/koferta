! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}


TEMPLATE = lib

#TARGET = ../kCommon

HEADERS += \
    LocalDatabase.h \
    SzukajKlienta.h \
    SzukajOferty.h \
    SzukajTowaru.h \
    functions.h \
    logger.h \
    AbstractDatabase.h \
    sqlitedatabase.h \
    PsqlDatabase.h \
    Database.h \
    SzukajTowaruModel.h \
    Merchandise.h

FORMS += \
    SzukajKlienta.ui \
    SzukajOferty.ui \
    SzukajTowaru.ui \
         
SOURCES += \
    LocalDatabase.cpp \
    SzukajKlienta.cpp \
    SzukajOferty.cpp \
    SzukajTowaru.cpp \
    functions.cpp \
    logger.cpp \
    AbstractDatabase.cpp \
    sqlitedatabase.cpp \
    PsqlDatabase.cpp \
    Database.cpp \
    SzukajTowaruModel.cpp \
    Merchandise.cpp
