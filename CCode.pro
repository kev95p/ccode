#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T21:18:25
#
#-------------------------------------------------
CONFIG      += release qscintilla2
macx {
    QMAKE_POST_LINK = install_name_tool -change libqscintilla2.12.dylib $$[QT_INSTALL_LIBS]/libqscintilla2.12.dylib $(TARGET)
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

TARGET = CCode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    highlighter.cpp \
    editor.cpp \
    widgettabsinferior.cpp \
    pestanaseditor.cpp \
    arboldir.cpp \
    acciones.cpp \
    acercade.cpp \
    barramenu.cpp

HEADERS  += mainwindow.h \
    highlighter.h \
    editor.h \
    widgettabsinferior.h \
    pestanaseditor.h \
    arboldir.h \
    acciones.h \
    acercade.h \
    barramenu.h

RESOURCES += \
    imagenes.qrc \
    keywords.qrc

FORMS += \
    acercade.ui

DISTFILES +=
