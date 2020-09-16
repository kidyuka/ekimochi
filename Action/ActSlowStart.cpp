#include "Action.h"
#include "DriveAction.h"
#include "DriveController.h"
#include "Util.h"

#define START    100
#define TARGET   400
#define RATE     50
#define INTERVAL 50

bool ActSlowStart::exec() {
    gDriveController.start();

    for(int speed = START; speed < TARGET; speed += RATE) {
        gDriveController.setSpeed(speed);
        tslp_tsk(INTERVAL * 1000);
    }
    gDriveController.setSpeed(TARGET);

    return true;
}
