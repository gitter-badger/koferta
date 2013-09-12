! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}


TEMPLATE = lib

#TARGET = ../kCommon

HEADERS += \
	LocalDatabase.h \
	SzukajKlienta.h \
	SzukajTowaru.h \
    functions.h

FORMS += \
	SzukajKlienta.ui \
	SzukajTowaru.ui \
         
SOURCES += \
	LocalDatabase.cpp \
	SzukajKlienta.cpp \
	SzukajTowaru.cpp \
    functions.cpp

