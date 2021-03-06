#-------------------------------------------------
#
# Project created by QtCreator 2020-11-05T14:50:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmulatorStackCPU
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

INCLUDEPATH += \
    ./Devices/ \
    ./Widgets/ \
    ./Builder/ \
    ./Programs/

SOURCES += \
        main.cpp \
    Devices/alu.cpp \
    Devices/stack.cpp \
    Devices/ram.cpp \
    Devices/cpu.cpp \
    mainwindow.cpp \
    Builder/lexer.cpp \
    Builder/builder.cpp

HEADERS += \
    Devices/alu.h \
    Devices/stack.h \
    Devices/ram.h \
    Devices/cpu.h \
    Devices/flags.h \
    mainwindow.h \
    Builder/lexer.h \
    Devices/consts.h \
    Builder/structs.h \
    Builder/builder.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    Programs/Lab1.txt \
    Programs/Lab2.txt
