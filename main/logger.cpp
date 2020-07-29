#include "logger.h"
#define LOGTODESKTOP

QString Logger::LogsPath =
        QDir::currentPath()
        + QDir::separator()
        + "Logs";

QString Logger::LogFilePath =
#ifndef LOGTODESKTOP
        Logger::LogsPath
        + QDir::separator()
        + QDateTime::currentDateTime().date().toString()
        + ".log";
#else
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
        + QDir::separator()
        + "logs.log";
#endif

bool Logger::enableLogging = false;

/// Create /Logs direcetory if it does not already exist
bool Logger::createLogsDirectory()
{
    QDir dir(Logger::LogsPath);

    if(dir.exists())
    {
        return true;
    }

    if(dir.mkpath(Logger::LogsPath))
    {
        return true;
    }
    else
    {
        qWarning() << "Could not create '/Logs' path!";

        return false;
    }
}

void Logger::Fatal(QString msg)
{
    errorLog = true;

    msg = QDateTime::currentDateTime().toString()
            + " FATAL: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Error(QString msg)
{
    errorLog = true;

    msg = QDateTime::currentDateTime().toString()
            + " ERROR: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Warn(QString msg)
{
    errorLog = true;

    msg = QDateTime::currentDateTime().toString()
            + " WARN: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Info(QString msg)
{
    errorLog = false;

    msg = QDateTime::currentDateTime().toString()
            + " INFO: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Debug(QString msg)
{
    errorLog = true;

    msg = QDateTime::currentDateTime().toString()
            + " DEBUG: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Trace(QString msg)
{
    errorLog = false;

    msg = QDateTime::currentDateTime().toString()
            + " TRACE: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Event(QString msg)
{
    errorLog = true;

    msg = QDateTime::currentDateTime().toString()
            + " EVENT: "
            + msg
            + "\n";

    writer(msg);
}

void Logger::Flush()
{
    QSharedMemory semaphore("flushingInProgress");

    if(semaphore.lock()) { Logger::Flush(); }
    else { Logger::flusher(); }
}

void Logger::flusher()
{
    QFile file(Logger::LogFilePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append) && !buffer.isEmpty())
    {
        file.write(buffer);
        buffer.clear();
        file.close();
    }
}

void Logger::writer(QString data)
{
    if(Logger::enableLogging)
    {
        QSharedMemory semaphore("loggingInProgress");

        if(semaphore.lock()) { Logger::writer(data); }
        else
        {
            if (buffer.size() > FLUSHRATE || errorLog == true)
            {
                Logger::flusher();
                buffer.clear();
            }

            buffer.append(data);
        }
    }
}
