TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    converter.cpp


LIBS += -LC:/Qt/Tools/mingw530_32/i686-w64-mingw32/lib/ -lOpenAL32

INCLUDEPATH += C:/Qt/Tools/mingw530_32/i686-w64-mingw32/include
DEPENDPATH += C:/Qt/Tools/mingw530_32/i686-w64-mingw32/include


LIBS += -LC:/Qt/Tools/mingw530_32/i686-w64-mingw32/lib/ -lalut

INCLUDEPATH += C:/Qt/Tools/mingw530_32/i686-w64-mingw32/include
DEPENDPATH += C:/Qt/Tools/mingw530_32/i686-w64-mingw32/include

HEADERS += \
    converter.h
