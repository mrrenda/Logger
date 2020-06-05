#include "logger.h"

/// Checkout - https://github.com/bimetek/qxtlogger/tree/master/qxtlogger

bool logger::enableLogging = false;
bool logger::enablePrinting = false;

QString logger::LogsPath =
        QDir::currentPath()
        + QDir::separator()
        + "Logs";

QString logger::LogFilePath =
        logger::LogsPath
        + QDir::separator()
        + QDateTime::currentDateTime().date().toString()
        + ".log";

QString logger::LogFileDesktop =
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
        + QDir::separator()
        + "Rasp.log";

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

/// Constructor - empty
logger::logger(QObject *parent) : QObject(parent) { }

/// Create /Logs direcetory if does not already exist
bool logger::createLogsDirectory()
{
    QDir dir(LogsPath);

    if(dir.exists())
    {
        return true;
    }

    if(dir.mkpath(LogsPath))
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
void logger::attach()
{
    createLogsDirectory();

    logger::enableLogging = true;
    qInstallMessageHandler(logger::handler);

    qInfo() << "Logger Initialized";

    logger::enablePrinting = true;
}

void logger::log(QFile file,
                 QString level,
                 const QMessageLogContext &context,
                 const QString &msg)
{
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream ts(&file);

        ts << QDateTime::currentDateTime().toString()
           << level
      #ifdef QT_DEBUG
           << context.file
           << " line: "
           << context.line
      #else
           << "[file path and line number not available in release mode]"
      #endif
           << " - "
           << msg
           << Qt::endl;

      #ifndef QT_DEBUG
           Q_UNUSED(context);
      #endif

        ts.flush();
        file.close();
    }
}

/// Handler for qMessageLoggers that will print and log these messages
void logger::handler(QtMsgType type,
                     const QMessageLogContext &context,
                     const QString &msg)
{
    if(logger::enableLogging)
    {
        QString level;

        switch (type)
        {
        case QtInfoMsg:
            level = " Info: ";
            break;
        case QtDebugMsg:
            level = " Debug: ";
            break;
        case QtWarningMsg:
            level = " Warning: ";
            break;
        case QtCriticalMsg:
            level = " Critical: ";
            break;
        case QtFatalMsg:
            level = " Fatal: ";
            break;
        }

//        QFile file(LogFilePath);
        QFile file (LogFileDesktop);

        QLockFile lock(file.fileName() +"l");
        lock.setStaleLockTime(50);

        logAgain:
        if(lock.tryLock())
        {
            if(file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream ts(&file);

                ts << QDateTime::currentDateTime().toString()
                   << level
      #ifdef QT_DEBUG
                   << context.file
                   << " line: "
                   << context.line
      #else
                   << "[file path and line number not available in release mode]"
      #endif
                   << " - "
                   << msg
                   << Qt::endl;

                ts.flush();
                file.close();
            }

            lock.unlock();
        }
        else
        {
            static qint32 i = 0;
            i++;
            qWarning() << "Another thread detected! Attemp #" << i;
            QThread::msleep(1);
            goto logAgain;
            qWarning() << "Could not lock the file!";
        }
    }

    if (logger::enablePrinting)
    {
        (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
    }
}
