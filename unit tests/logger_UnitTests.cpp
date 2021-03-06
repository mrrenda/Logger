#include "logger_UnitTests.h"

loggerUnitTests::loggerUnitTests(QObject *parent) : QObject(parent) { }

QString logString = "Testing Logger";

void loggerUnitTests::loggingWriteTest()
{
    log().Info(logString);
    log().Flush();
}

void loggerUnitTests::loggingReadTest()
{
    QFile file(Logger::LogFilePath);

    if(!file.exists())
    {
        QString message = "Log files not found!\n"
                + Logger::LogFilePath + " missing";

        QFAIL(message.toStdString().data());

        return;
    }
    else
    {
        if(!file.open(QIODevice::ReadOnly))
        {
            QFAIL(file.errorString().toStdString().data());
            return;
        }

        bool logStringFound = false;

        while (!file.atEnd())
        {
            QString line(file.readLine());

            if(line.trimmed().contains(logString))
            {
                logStringFound = true;
            }
        }

        if (!logStringFound)
        {
            QFAIL("Log file does not contain logged string!");
        }

        file.close();
    }
}

void loggerUnitTests::loggingBenchmarkTest()
{
    QBENCHMARK
    {
        log().Info("logging benchmark test");
    }
    log().Flush();
}
