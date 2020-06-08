#ifndef LOGGERUNITTESTS_H
#define LOGGERUNITTESTS_H

#include <QObject>
#include <QTest>

#include "logger.h"

class loggerUnitTests : public QObject
{
    Q_OBJECT
public:
    explicit loggerUnitTests(QObject *parent = nullptr);

private slots:
    void loggingWriteTest();
    void loggingReadTest();
    void loggingBenchmarkTest();
};

#endif // LOGGERUNITTESTS_H
