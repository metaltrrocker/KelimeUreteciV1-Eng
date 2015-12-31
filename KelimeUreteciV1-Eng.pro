#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T21:44:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KelimeUreteciV1-Eng
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    degisken.h \

FORMS    += mainwindow.ui

DISTFILES += \
    Splashlogo.png \
    ReadMe \
    Splashlogo \
    winikon.rc \
    kelimeureteci.rc \
    wordlystgenyrator.ico

RESOURCES += \
    ikon.qrc \
    arkaplan.qrc
RC_FILE = winikon.rc
