#include "Device.h"
#include "DriveController.h"
#include "LineTraceController.h"
#include "MotorController.h"
#include "ColorSensor.h"
#include "Button.h"
#include "Util.h"

void devicecontroller_initilize() {
    button_initialize();
    motorcontroller_initilze();
}

void devicecontroller_task_start() {
    act_tsk(DEVICECONTROLLER_TASK);
}

void devicecontroller_task(intptr_t exinf) {
    while(true) {
        gLineTraceController.runTask();
        gDriveController.runTask();
        gLeftMotor.runTask();
        gRightMotor.runTask();
        tslp_tsk(25 * 1000);
    }
}
