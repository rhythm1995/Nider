#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T22:06:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NIDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    project.cpp \
    highlighter.cpp \
    newprojectwindow.cpp \
    settingwindow.cpp \
    jsonhelper.cpp \
    errorhelper.cpp \
    filehelper.cpp \
    projectentity.cpp \
    filemanager.cpp \
    editor.cpp

HEADERS += \
        mainwindow.h \
    project.h \
    highlighttype.h \
    highlighter.h \
    newprojectwindow.h \
    settingwindow.h \
    jsonhelper.h \
    errorhelper.h \
    filehelper.h \
    projectentity.h \
    filemanager.h \
    editor.h

FORMS += \
        mainwindow.ui \
    newprojectwindow.ui \
    settingwindow.ui

RESOURCES += \
    assets.qrc

DISTFILES += \
    ../nide_project/project1/project1.nproj \
    ../nide_project/newProject/newProject.nproj
