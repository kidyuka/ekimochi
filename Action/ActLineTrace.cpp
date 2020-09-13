#include "Action.h"
#include "DriveAction.h"
#include "LineTraceController.h"
#include "Odometor.h"

bool ActLineTrace::exec() {
    OdoInfo p1, p2;

    gOdometor.get(&p1);

    mActSlowStart.run();

    while(true) {
        gOdometor.get(&p2);
        float distance = get_distance(&p1, &p2);
        if(distance > 20) 
            break;
        p1 = p2;
    }

    gLineTraceController.start();
    

}
