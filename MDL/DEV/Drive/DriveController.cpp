#include "DriveController.h"
#include "cfg/DriveController_cfg.h"
#include "LineTraceController.h"

#include "MotorController.h"
#include "Util.h"

#define white 38
#define black 0

#define SPEED 150
#define R_RATE  3
#define L_RATE  2.5

void drivecontroller_task_start() {
    act_tsk(DRIVECONTROLLER_TASK);
}

void drivecontroller_task(intptr_t exinf) {
    while(true) {
        linetrace_controller_task();
        tslp_tsk(100 * 1000);
    }
}
