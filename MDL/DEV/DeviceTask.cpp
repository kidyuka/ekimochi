#include "Device.h"
#include "DriveController.h"
#include "LineTraceController.h"
#include "MotorController.h"
#include "ColorSensor.h"
#include "Button.h"
#include "Util.h"

void device_controller_initilize() {
    button_initialize();
    motorcontroller_initilze();
}

void device_sensor_initilize() {

}

void device_sensor_task(intptr_t exinf) {
    static uint32_t count = 0;

    if(count % 10 == 0)
        colorsensor_task();

    count++;
}

void device_controller_task(intptr_t exinf) {
    gLineTraceController.runTask();
    gDriveController.runTask();
    gLeftMotor.runTask();
    gRightMotor.runTask();
}

void device_task(intptr_t exinf) {
    static uint32_t count = 0;

    if(count % 2 == 0)
        act_tsk(DEVICE_SENSOR_TASK);

    if(count % 5 == 0)
        act_tsk(DEVICE_CONTROLLER_TASK);

    count++;
}

void device_task_start() {
    sta_cyc(DEVICE_TASK);
}