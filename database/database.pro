#-----------------------------------------------------------------------------
#
#    kOferta - system usprawniajacy proces ofertowania
#	 komponent kDatabase odpowiedzialny za synchronizację głownej bazy
#	 danych i lokalnej, oraz możliwość modyfikacji danych w głownej bazie 

! include(../base.pri) {
    error( "Couldn't find the common.pri file!" )
}



TARGET 	  = ../kDatabase
CONFIG   += console
#CONFIG   += app_bundle

TEMPLATE = app

LIBS += -L../common -lcommon

HEADERS += \
    foo.h \
	Macros.h \
	Database.h \
	Logowanie.h \
	NowyKlient.h \
	NowyTowar.h \
	NowyUser.h \
	SHA1.h \
	EdycjaKlienta.h \
	EdycjaTowaru.h \
	User.h \
	EdycjaKombo.h

FORMS += \
	Logowanie.ui \
	EdycjaKlienta.ui \
	EdycjaTowaru.ui \
	NowyKlient.ui \
	NowyTowar.ui \
	NowyUser.ui \
	EdycjaKombo.ui 

SOURCES += main.cpp \
    foo.cpp \
	Database.cpp \
	Logowanie.cpp \
	NowyKlient.cpp \
	NowyTowar.cpp \
	NowyUser.cpp \
	SHA1.cpp \
	EdycjaKlienta.cpp \
	EdycjaTowaru.cpp \
	User.cpp \
	EdycjaKombo.cpp

