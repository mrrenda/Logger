#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QStandardPaths>
#include <QMetaObject>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

#define FLUSHRATE 100000

#ifdef QT_DEBUG
//#define log Logger(__FILE__,__LINE__).Log
#else
//#define log Logger().Log
#endif

#define log Logger::getInstance

class Logger
{
public:

    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

public:
//    Logger(QString sFileName, int nLineNo);
    void Flush();

    void Fatal(QString msg);
    void Error(QString msg);
    void Warn(QString msg);
    void Info(QString msg);
    void Debug(QString msg);
    void Trace(QString msg);
    void Event(QString msg);

public:
    static QString LogsPath;
    static QString LogFilePath;
    static bool enableLogging;

private:
    Logger()
    {
        createLogsDirectory();
        Logger::enableLogging = true;
        buffer.reserve(FLUSHRATE + 1000);
    }
    ~Logger() { flusher(); }
    static bool createLogsDirectory();
    void writer(QString data);
    void flusher();

private:
    QString sFileName = "";
    int nLineNo = 0;
    QByteArray buffer;
};

#endif // LOGGER_H
