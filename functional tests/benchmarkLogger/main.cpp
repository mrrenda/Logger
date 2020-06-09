#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger::attach();

    int i = 0;
    qint64 timeTaken;

    QElapsedTimer timer;
    timer.start();

    for(;i < 100; i++)
    {
        log("benchmark log"); // FIXME - Bug somewhere, on windows I only read 39 lines of logs
    }

    timeTaken = timer.nsecsElapsed();

    qDebug() << "Time elapsed " << timeTaken << " nanoseconds";
    qDebug() << "Average msec " << (double)timeTaken / 100000;

    return a.exec();
}
