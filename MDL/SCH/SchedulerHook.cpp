#include "Scheduler.h"

#include "Device.h"
#include "Util.h"

void sch_initilize_hook() {
    device_controller_initilize();
    device_sensor_initilize();

    device_task_start();
}