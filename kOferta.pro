#-----------------------------------------------------------------------------
#
#    kOferta - system usprawniajacy proces ofertowania
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

TARGET = kOferta

QT += sql printsupport widgets

CONFIG += c++11

TEMPLATE = app

DEFINES += VER=2.4

win32 {
    QMAKE_CXXFLAGS += /nologo #/O2 /Wall

    QMAKE_LFLAGS_RELEASE += /NODEFAULTLIB:LIBCMT
    QMAKE_LFLAGS_DEBUG += /NODEFAULTLIB:LIBCMT

    CONFIG += qt windows #release

    #INCLUDEPATH += "C:/Program Files/MySQL/MySQL Server 5.7/include"

    LIBS += -L"C:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64" -lUser32 -lAdvAPI32
    #LIBS += -L"C:/Program Files/MySQL/MySQL Server 5.7/lib" -llibmysql

    DEFINES += WIN32
#    DEFINES += RELEASE
    DEFINES += NOSSL

#    INCLUDEPATH += "C:/Program Files/MySQL/MySQL Connector C 6.1 6.1.2/include"
    LIBS += -L"C:/Program Files/MySQL/MySQL Connector C 6.1 6.1.2/lib" -llibmysql
}

unix {
    QMAKE_CXXFLAGS += -Wall -Werror -Wextra
    LIBS += -L/usr/lib/mysql -lmysqlclient
    #DEFINES += NOSSL
    DEFINES += RELEASE
}

DEPENDPATH += . res 

HEADERS += \
    Database.h \
    EdycjaKlienta.h \
    LoadDialog.h \
    Logowanie.h \
    Macros.h \
    MainWindow.h \
    NowyKlient.h \
    NowyTowar.h \
    SzukajKlienta.h \
    SzukajOferty.h \
    SzukajTowaru.h \
    User.h \
    WyborKlienta.h \
    WyborTowaru.h \
    EdycjaKombo.h  \
    functions.h \
    Logger.h

FORMS += \
    EdycjaKlienta.ui \
    LoadDialog.ui \
    Logowanie.ui \
    MainWindow.ui \
    NowyKlient.ui \
    NowyTowar.ui \
    SzukajKlienta.ui \
    SzukajOferty.ui \
    SzukajTowaru.ui \
    WyborKlienta.ui \
    WyborTowaru.ui \
    EdycjaKombo.ui

SOURCES += \
    Database.cpp \
    EdycjaKlienta.cpp \
    LoadDialog.cpp \
    Logowanie.cpp \
    Main.cpp \
    MainWindow.cpp \
    NowyKlient.cpp \
    NowyTowar.cpp \
    SzukajKlienta.cpp \
    SzukajOferty.cpp \
    SzukajTowaru.cpp \
    User.cpp \
    WyborKlienta.cpp \
    WyborTowaru.cpp \
    EdycjaKombo.cpp \
    Logger.cpp

RESOURCES += res/zasoby.qrc

OTHER_FILES += \
    changelog.txt \
    LICENSE.md \
    res/gpl-3.0.txt \
    res/gpl-3.0.html \
    README.md \
    hosts
