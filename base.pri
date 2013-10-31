DEFINES += VER=2.9

QT       = core sql widgets

INCLUDEPATH += . .. ../common
#WARNINGS += -Wall
QMAKE_CXXFLAGS += -std=c++0x

win32 { #nmake & M$ compiler

    CONFIG += qt windows release

    QMAKE_CXXFLAGS += /nologo /O2 #/Wall

    QMAKE_LFLAGS_RELEASE += /NODEFAULTLIB:LIBCMT
    #   QMAKE_LFLAGS_DEBUG += /NODEFAULTLIB:LIBCMT

    #    INCLUDEPATH += C:\\mysql\\include
    INCLUDEPATH += C:\\koferta_src

    #    LIBS += -L"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.0A\\Lib" -lUser32 -lAdvAPI32
    #    LIBS += -LC:\\mysql\\lib -lmysqlclient -llibmysql

    DEFINES += WIN32
    DEFINES += RELEASE
}

unix {
  #  LIBS += -L/usr/lib/mysql -lmysqlclient
    DEFINES += NOSSL
 #   DEFINES += RELEASE
}

#TEMPLATE = lib

# The following keeps the generated files at least somewhat separate 
# from the source files.
OBJECTS_DIR = ../temp
UI_DIR      = ../temp
MOC_DIR     = ../temp
RCC_DIR     = ../temp


