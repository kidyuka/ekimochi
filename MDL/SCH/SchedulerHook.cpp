#include "Scheduler.h"

#include "Device.h"
#include "Action.h"
#include "Util.h"

void sch_initilize_hook() {
    device_controller_initilize();
    device_sensor_initilize();

    device_task_start();
    action_task_start();
}