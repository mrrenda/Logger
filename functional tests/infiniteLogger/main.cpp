#include <QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger::attach();
    int i = 0;

    while(1)
    {
        log(LogLevel::DEBUG, "loop");
        qDebug() << "logged " << ++i;
    }

    return a.exec();
}
