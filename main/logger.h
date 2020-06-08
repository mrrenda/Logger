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
#define log Logger(__FILE__,__LINE__).Log
#else
#define log Logger().Log
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
Q_DECLARE_METATYPE(LogLevel)

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(QObject *parent = nullptr);
    Logger(QString sFileName, int nLineNo);
    void Log(QString msg);
    void Log(LogLevel lvl, QString msg);
    static void attach();

public:
    static QString LogsPath;
    static QString LogFilePath;
    static bool enableLogging;

private:
    static bool createLogsDirectory();
//    void write(LogLevel lvl, QString msg);

private:
    LogLevel logType;
    QString sFileName = "";
    int nLineNo = 0;

public slots:
    void write(LogLevel lvl, QString msg);
};

#endif // LOGGER2_H
