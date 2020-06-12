TEMPLATE = subdirs

SUBDIRS += \
    ./main/logger.pro \
    # UNIT TESTS #
    "./unit tests/logger_UnitTests.pro" \
    # FUNCTIONAL TESTS #
    "./functional tests/benchmarkLogger/benchmarkLogger.pro" \
    "./functional tests/infiniteLogger/infiniteLogger.pro" \

# to build the projects sequentially as listed in SUBDIRS
  CONFIG += ordered
