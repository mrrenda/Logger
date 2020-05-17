#ifndef INITLOGGER_H
#define INITLOGGER_H

#include "logger.h"

class InitLogger
{
public:
    static void initLogger() {
        logger::attach();   //initialize the logger
    }
};

#endif // INITLOGGER_H
