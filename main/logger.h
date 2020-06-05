#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QLoggingCategory>
#include <QLockFile>
#include <QStandardPaths>
#include <QThread>

#include <iostream>

class logger : public QObject
{
    Q_OBJECT
private:
    explicit logger(QObject *parent = nullptr);

    static bool createLogsDirectory();

    static void handler(QtMsgType type,
                        const QMessageLogContext &context,
                        const QString & msg);
public:
    static QString LogsPath;
    static QString LogFilePath;
    static QString LogFileDesktop;

    static bool enableLogging;
    static bool enablePrinting;

    static void attach();
};

#endif // LOGGER_H
