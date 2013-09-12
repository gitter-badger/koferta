! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}

TARGET = ../kOferta

TEMPLATE = app

LIBS += -L../common -lcommon

HEADERS += \
	LoadDialog.h \
	MainWindow.h \
	SzukajOferty.h \
	WyborKlienta.h \
	WyborTowaru.h \
	Towar.h \
	TowarModel.h \
	TowarDelegate.h \ 

FORMS += \
	LoadDialog.ui \
	MainWindow.ui \
	SzukajOferty.ui \
	WyborKlienta.ui \ 
	WyborTowaru.ui
         
SOURCES += \
	LoadDialog.cpp \
	Main.cpp \
	MainWindow.cpp \
	SzukajOferty.cpp \
	WyborKlienta.cpp \        
	WyborTowaru.cpp \
	Towar.cpp \
	TowarModel.cpp \
	TowarDelegate.cpp 

