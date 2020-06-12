#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger::attach();

    int i = 0;
    int logCount = 10000;
    qint64 timeTaken;

    QElapsedTimer timer;
    timer.start();

    for(;i < logCount; i++)
    {
        Logger::getInstance().Log("benchmark log");
    }

    Logger::getInstance().Flush();

    timeTaken = timer.nsecsElapsed();

    qDebug() << "Time elapsed " << timeTaken << " nanoseconds";
    qDebug() << "Average msec " << (double)timeTaken / (1000 * logCount);

    return a.exec();
}
