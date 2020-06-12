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

/// Attach handler to qMessageLoggers
void Logger::attach()
{
    createLogsDirectory();
    Logger::enableLogging = true;
}

void Logger::Log(QString msg)
{
    Logger::Log(LogLevel::INFO, msg);
}

void Logger::Log(LogLevel lvl, QString msg)
{
    if(Logger::enableLogging)
    {
        QString dateTime = QDateTime::currentDateTime().toString();

        QSharedMemory semaphore("loggingInProgress");

        if(semaphore.lock())
        {
            Logger::Log(lvl, msg);
        }
        else
        {
//            QtConcurrent::run(this, &Logger::write, lvl, msg, dateTime);
            Logger::writer(lvl, msg, dateTime);
        }
    }
}

void Logger::Flush()
{
    QSharedMemory semaphore("flushingInProgress");

    if(semaphore.lock())
    {
        Logger::Flush();
    }
    else
    {
//        QtConcurrent::run(this, &Logger::flusher);
        Logger::flusher();
    }
}

void Logger::flusher()
{
    QFile file(Logger::LogFilePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        file.write(buffer);
        buffer.clear();
        file.close();
    }
}

void Logger::writer(LogLevel lvl, QString msg, QString dateTime)
{

    QString sLvl;

    switch (lvl)
    {
    case LogLevel::FATAL:
        sLvl = " FATAL: ";
        break;
    case LogLevel::ERROR:
        sLvl = " ERROR: ";
        break;
    case LogLevel::WARN:
        sLvl = " WARN: ";
        break;
    case LogLevel::INFO:
        sLvl = " INFO: ";
        break;
    case LogLevel::DEBUG:
        sLvl = " DEBUG: ";
        break;
    case LogLevel::TRACE:
        sLvl = " TRACE: ";
        break;
    case LogLevel::EVENT:
        sLvl = " EVENT: ";
        break;
    }

    buffer.append(dateTime);
    buffer.append(sLvl);
    buffer.append(msg);
    buffer.append("\n");

    if (buffer.size() > FLUSHRATE)
    {
        Logger::flusher();
        buffer.clear();
    }
}
