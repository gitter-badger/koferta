! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}


TEMPLATE = lib

#TARGET = ../kCommon

HEADERS += \
	SzukajKlienta.h \
	SzukajTowaru.h

FORMS += \
	SzukajKlienta.ui \
	SzukajTowaru.ui \
         
SOURCES += \
	SzukajKlienta.cpp \
	SzukajTowaru.cpp

