#include "logger_UnitTests.h"

loggerUnitTests::loggerUnitTests(QObject *parent) : QObject(parent) { }

QString logString = "Testing Logger";

void loggerUnitTests::loggingWriteTest()
{
    InitLogger::initLogger();
    logger::enableLogging = true;

    qInfo() << logString;
}

void loggerUnitTests::loggingReadTest()
{
    QFile file(logger::LogFilePath);

    if(!file.exists())
    {
        QFile file(logger::LogFileDesktop);

        if(!file.exists())
        {
            QString message = "Log files not found!\n"
                    + logger::LogFilePath + " missing\n"
                    + logger::LogFileDesktop + " missing";

            QFAIL(message.toStdString().data());

            return;
        }

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
        qInfo() << "logging benchmark test";
    }
}
