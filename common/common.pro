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
    AbstractDatabase.h \
    PsqlDatabase.h \
    Database.h \
    SzukajTowaruModel.h \
    Merchandise.h \
    SQLiteDatabase.h \
    Logger.h

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
    AbstractDatabase.cpp \
    PsqlDatabase.cpp \
    Database.cpp \
    SzukajTowaruModel.cpp \
    Merchandise.cpp \
    SQLiteDatabase.cpp \
    Logger.cpp
