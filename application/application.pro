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
	Towar.h \
	TowarModel.h \
	TowarDelegate.h \ 

FORMS += \
	LoadDialog.ui \
	MainWindow.ui \
	WyborKlienta.ui \ 
	WyborTowaru.ui
         
SOURCES += \
	LoadDialog.cpp \
	Main.cpp \
	MainWindow.cpp \
	WyborKlienta.cpp \        
	WyborTowaru.cpp \
	Towar.cpp \
	TowarModel.cpp \
	TowarDelegate.cpp 

