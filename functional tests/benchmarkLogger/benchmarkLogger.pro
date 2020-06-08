# Qt MODULES
QT -= gui

# PROJECT CONFIGURATION
CONFIG += c++11 console
CONFIG -= app_bundle

# PROJECT SOURCES
SOURCES += main.cpp

# DEFINITIONS
win32 { DEFINES += __WINDOWS__ } # FOR WINDOWS SYSTEMS
unix { !macx { DEFINES += __linux__ } } # FOR LINUX SYSTEMS

# PROJECT OUTPUT INFO
TARGET = benchmarkLogger
DESTDIR = $$_PRO_FILE_PWD_/../../bin

# STATIC LIBRARIES
INCLUDEPATH += $$_PRO_FILE_PWD_/../../main
LIBS += -L$$_PRO_FILE_PWD_/../../bin -llogger
