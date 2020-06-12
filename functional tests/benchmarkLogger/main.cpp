#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int i = 0;
    int logCount = 10000;
    qint64 timeTaken;

    QElapsedTimer timer;
    timer.start();

    for(;i < logCount; i++)
    {
        log().Info("benchmark log #" + QString::number(i));
    }

    log().Flush();

    timeTaken = timer.nsecsElapsed();

    qDebug() << "Time elapsed " << timeTaken << " nanoseconds";
    qDebug() << "Average usec " << (double)timeTaken / (1000 * logCount);

    return a.exec();
}
