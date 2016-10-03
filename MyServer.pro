QT += core
QT -= gui

CONFIG += c++11

TARGET = MyServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    MyServer.cpp

HEADERS += \
    MyServer.h
