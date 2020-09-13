#ifndef DRIVEACTION_H
#define DRIVEACTION_H

#include "Action.h"

class ActSlowStart : public Action {
public:
    bool exec();
};

class ActLineTrace : public Action {
private:
    ActSlowStart mActSlowStart;
public:
    bool exec();
};

#endif