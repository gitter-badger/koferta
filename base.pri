DEFINES += VER=3.0

QT       = core sql gui

INCLUDEPATH += . ..
WARNINGS += -Wall

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
#    QMAKE_CXXFLAGS += -Wall -Werror -Wextra
    LIBS += -L/usr/lib/mysql -lmysqlclient
    #DEFINES += NOSSL
 #   DEFINES += RELEASE
}

#TEMPLATE = lib

# The following keeps the generated files at least somewhat separate 
# from the source files.
OBJECTS_DIR = temp
UI_DIR 		= temp
MOC_DIR 	= temp
RCC_DIR 	= temp


