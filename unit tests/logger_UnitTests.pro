# Qt MODULES
QT += testlib
QT -= gui

# PROJECT CONFIGURATION
CONFIG += c++11 console
CONFIG -= app_bundle

# PROJECT HEADERS
HEADERS += \
    logger_UnitTests.h

# PROJECT SOURCES
SOURCES += \
    logger_UnitTests.cpp \
    main.cpp

# DEFINITIONS
win32 { DEFINES += __WINDOWS__ } # FOR WINDOWS SYSTEMS
unix { !macx { DEFINES += __linux__ } } # FOR LINUX SYSTEMS

# PROJECT OUTPUT INFO
TARGET = loggerUnitTest
DESTDIR = $$_PRO_FILE_PWD_/../bin/

# STATIC LIBRARIES
INCLUDEPATH += $$_PRO_FILE_PWD_/../main/
LIBS += -L$$_PRO_FILE_PWD_/../bin/ -llogger
