#-----------------------------------------------------------------------------
#
#    kOferta - system usprawniajacy proces ofertowania
#	 komponent kDatabase odpowiedzialny za synchronizację głownej bazy
#	 danych i lokalnej, oraz możliwość modyfikacji danych w głownej bazie 
#    Copyright (C) 2011  Kamil 'konserw' Strzempowicz, konserw@gmail.com
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#----------------------------------------------------------------------------

QT       += core sql
QT       -= gui

TARGET 	  = kDatabase
CONFIG   += console
CONFIG   += app_bundle

TEMPLATE = app

win32 { #nmake & M$ compiler
    QMAKE_CXXFLAGS += /nologo /O2 #/Wall

    QMAKE_LFLAGS_RELEASE += /NODEFAULTLIB:LIBCMT
    QMAKE_LFLAGS_DEBUG += /NODEFAULTLIB:LIBCMT

    CONFIG += qt windows release

    INCLUDEPATH += C:\\mysql\\include
    INCLUDEPATH += C:\\koferta_src

    LIBS += -L"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.0A\\Lib" -lUser32 -lAdvAPI32
    LIBS += -LC:\\mysql\\lib -lmysqlclient -llibmysql

    DEFINES += WIN32
    DEFINES += RELEASE
}
unix {
	QMAKE_CXXFLAGS += -Wall -Wextra -Werror
	LIBS += -L/usr/lib/mysql -lmysqlclient
}

OBJECTS_DIR =   temp
UI_DIR =        temp
MOC_DIR =       temp
RCC_DIR =       temp

DEPENDPATH += . ../res 

HEADERS += \
    foo.h \
	Database.h \
	Logowanie.h \
	NowyKlient.h \
	NowyTowar.h \
	NowyUser.h \
	SHA1.h \
	EdycjaKlienta.h \
	EdycjaTowaru.h \
	../SzukajKlienta.h \
	../SzukajTowaru.h \ \
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
	../SzukajKlienta.cpp \
	../SzukajTowaru.cpp \ \
	User.cpp \
	EdycjaKombo.cpp

RESOURCES += ../res/zasoby.qrc

OTHER_FILES += \
    changelog.txt \
    res/LICENSE \
    res/gpl-3.0.txt \
    res/gpl-3.0.html \
    res/SHA1_LICENSE \
    ../README.md
