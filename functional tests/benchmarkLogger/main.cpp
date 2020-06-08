#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger::attach();
    int i = 0;

    QElapsedTimer timer;
    timer.start();

    while(i != 100)
    {
        log(LogLevel::INFO, "peeked " + QString::number(i));
        qDebug() << "logged " << ++i;
    }

    qDebug() << "Time elapsed " << timer.nsecsElapsed() << " nanoseconds";
    qDebug() << "Average msec " << (double)timer.nsecsElapsed()/100000;

    a.exec();

    return 0;
}
