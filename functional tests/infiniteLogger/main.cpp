#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger::attach();

    qDebug() << "Started Logging";

    while(1)
    {
        Logger::getInstance().Log(LogLevel::DEBUG, "loop");
    }

    return a.exec();
}
