#-------------------------------------------------
#
# Project created by QtCreator 2014-04-05T19:19:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skype-mood
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    skypecontactpreview.cpp \
    progressdialog.cpp \
    htmldelegate.cpp \
    menudialog.cpp \
    entitledseparator.cpp \
    editableintsizecombobox.cpp \
    tagsplaintextedit.cpp

HEADERS  += mainwindow.h \
    skypecontactpreview.h \
    progressdialog.h \
    htmldelegate.h \
    menudialog.h \
    defines.h \
    entitledseparator.h \
    editableintsizecombobox.h \
    tagsplaintextedit.h

TRANSLATIONS  += fr.ts

RESOURCES += \
    ressources.qrc
