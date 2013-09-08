#-------------------------------------------------
#
# Project created by konserw (C)
#
#-------------------------------------------------

QT       += core sql
QT       -= gui

TARGET 	  = dbTools
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
LIBS += -L/usr/lib/mysql -lmysqlclient

OBJECTS_DIR =   temp
UI_DIR =        temp
MOC_DIR =       temp
RCC_DIR =       temp

SOURCES += main.cpp \
    foo.cpp

HEADERS += \
    foo.h

RESOURCES += \
    zasoby.qrc
