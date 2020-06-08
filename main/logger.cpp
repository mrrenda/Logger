#include "logger.h"
#define LOGTODESKTOP

QString Logger::LogsPath =
        QDir::currentPath()
        + QDir::separator()
        + "Logs";

QString Logger::LogFilePath =
#ifndef LOGTODESKTOP
        Logger2::LogsPath
        + QDir::separator()
        + QDateTime::currentDateTime().date().toString()
        + ".log";
#else
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
        + QDir::separator()
        + "logs.log";
#endif

bool Logger::enableLogging = false;

Logger::Logger(QObject *parent) : QObject(parent) {}

Logger::Logger(QString sFileName, int nLineNo)
{
    this->sFileName = sFileName;
    this->nLineNo   = nLineNo;
}

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
    QSharedMemory semaphore("loggingInProgress");

    if(semaphore.lock())
    {
        QThread::msleep(1);
        Logger::Log(lvl, msg);
    }
    else
    {
        QtConcurrent::run(this, &Logger::write, lvl, msg);
    }
}

void Logger::write(LogLevel lvl, QString msg)
{
    if(Logger::enableLogging)
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

        QFile file(Logger::LogFilePath);

        if(1)
        {
            if(file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream ts(&file);

                ts << QDateTime::currentDateTime().toString()
                   << sLvl
      #ifdef QT_DEBUG
//                   << sFileName
                   << " line: "
//                   << nLineNo
      #else
                   << "[file path and line number not available in release mode]"
      #endif
                   << " - "
                   << msg
                   << Qt::endl;

                ts.flush();
                file.close();
            }
        }
        else
        {
            //retry logging
        }
    }
}
