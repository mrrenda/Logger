#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDebug>
#include "logger.h"

int main()
{
    int i = 0;
    int logCount = 10000;
    qint64 timeTaken;

    QElapsedTimer timer;
    timer.start();

    for(;i < logCount; i++)
    {
//        log().Info("benchmark log #" + QString::number(i));
//        log().test("benchmark log #", i);
    }

    QString samil = "samil";
    std::string asd = log().LOG("renda", "muhammed", 2, samil);
    qDebug() << QString::fromStdString(asd);

    log().Flush();

    timeTaken = timer.nsecsElapsed();

    qDebug() << "Time elapsed " << timeTaken << " nanoseconds";
    qDebug() << "Average time " << (double)timeTaken / (1000 * logCount) << " usec";

    return 0;
}
