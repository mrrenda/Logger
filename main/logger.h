#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QSharedMemory>
#include <QDebug>

#define FLUSHRATE 100000

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
    QByteArray buffer;
    bool errorLog;
};

#endif // LOGGER_H
