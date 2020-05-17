TEMPLATE = subdirs

SUBDIRS += \
    ./main/logger.pro \
    # UNIT TESTS #
    "./unit tests/logger_UnitTests.pro"

# to build the projects sequentially as listed in SUBDIRS
  CONFIG += ordered
