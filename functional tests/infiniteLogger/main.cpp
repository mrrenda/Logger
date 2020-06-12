#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Started Logging";

    while(1)
    {
        log().Debug("loop");
    }

    return a.exec();
}
