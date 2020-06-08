# Qt MODULES
QT -= gui

# PROJECT CONFIGURATION
CONFIG += c++11 staticlib
TEMPLATE = lib

# PROJECT HEADERS
HEADERS += \
    logger.h \

# PROJECT SOURCES
SOURCES += \
    logger.cpp \

# DEFINITIONS
win32 { DEFINES += __WINDOWS__ } # FOR WINDOWS SYSTEMS
unix { !macx { DEFINES += __linux__ } } # FOR LINUX SYSTEMS

# PROJECT OUTPUT INFO
TARGET = logger
DESTDIR = $$_PRO_FILE_PWD_/../bin
