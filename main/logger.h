#ifndef LOGGER2_H
#define LOGGER2_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QStandardPaths>
#include <QMetaObject>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

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

public:
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

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
    Logger() { buffer.reserve(2000000000); }
    static bool createLogsDirectory();
    void write(LogLevel lvl, QString msg, QString dateTime);
    void flusherThread();

private:
    LogLevel logType;
    QString sFileName = "";
    int nLineNo = 0;
    QByteArray buffer;
};

#endif // LOGGER2_H
