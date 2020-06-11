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

//Logger::Logger() { }

//Logger::Logger(QString sFileName, int nLineNo)
//{
//    this->sFileName = sFileName;
//    this->nLineNo   = nLineNo;
//}

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
//    Logger::getInstance();
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
        QSharedMemory semaphore("loggingInProgress");

        if(semaphore.lock())
        {
//            QThread::msleep(1);
            Logger::Log(lvl, msg);
        }
        else
        {
            QtConcurrent::run(this, &Logger::write, lvl, msg);
        }
    }
}

void Logger::Flush()
{
//    QSharedMemory semaphore("flushingInProgress");

//    if(semaphore.lock())
//    {
//        QThread::msleep(1);
//        Logger::Flush();
//    }
//    else
//    {
//        QtConcurrent::run(this, &Logger::flusher);
//    }
    Logger::flusher();
}

void Logger::flusher()
{
    QFile file(Logger::LogFilePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream ts(&file);

        ts << buffer.data();

        ts.flush();
        file.close();
    }
}

void Logger::write(LogLevel lvl, QString msg)
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


    buffer.append(QDateTime::currentDateTime().toString());
    buffer.append(sLvl);
//#ifdef QT_DEBUG
//       << sFileName
//       << " line: "
//       << nLineNo
        /* FIXME - Bug at "log" macro in header
        current method of obtaining file path
        and line number is not thread safe */
//#else
//       << "[file path and line number not available in release mode]"
//#endif
    buffer.append(" - ");
    buffer.append(msg);
    buffer.append("\n");
//    buffer.append(Qt::endl);

//    ts.flush();
}
