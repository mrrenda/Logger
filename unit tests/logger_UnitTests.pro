# Qt MODULES
QT += testlib
QT -= gui

# PROJECT CONFIGURATION
CONFIG += c++11 console
CONFIG -= app_bundle

# PROJECT HEADERS
HEADERS += \
    initLogger.h \
    logger_UnitTests.h

# PROJECT SOURCES
SOURCES += \
    main.cpp \
    logger_UnitTests.cpp

# DEFINITIONS
win32 { DEFINES += __WINDOWS__ } # FOR WINDOWS SYSTEMS
unix { !macx { DEFINES += __linux__ } } # FOR LINUX SYSTEMS

# STATIC LIBRARIES
INCLUDEPATH += $$PWD/../main


LIBS += -L$$OUT_PWD/../main/ -llogger
#message($$OUT_PWD)
#CONFIG(debug, debug|release) {
#    LIBS += -L$$OUT_PWD/../main/debug/ -llogger
#} else {
#    LIBS += -L$$OUT_PWD/../main/release/ -llogger
#}
