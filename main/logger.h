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

enum LogLevel
{
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
    EVENT
};

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
    void Log(QString msg);
    void Log(LogLevel lvl, QString msg);
    void Flush();
    static void attach();

public:
    static QString LogsPath;
    static QString LogFilePath;
    static bool enableLogging;

private:
    Logger() { buffer.reserve(FLUSHRATE + 1000); }
    ~Logger() { flusher(); }
    static bool createLogsDirectory();
    void writer(LogLevel lvl, QString msg, QString dateTime);
    void flusher();

private:
    LogLevel logType;
    QString sFileName = "";
    int nLineNo = 0;
    QByteArray buffer;
};

#endif // LOGGER_H
