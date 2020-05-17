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

#TODO
# Default rules for deployment.
unix { target.path = $$[QT_INSTALL_PLUGINS]/generic }
!isEmpty(target.path): INSTALLS += target
