#include "Action.h"
#include "DriveAction.h"
#include "LineTraceController.h"
#include "Odometor.h"

bool ActLineTrace::exec() {
    OdoData p1, p2;

    gOdometor.get(&p1);

    mActSlowStart.run();

    gLineTraceController.start();
    

}
