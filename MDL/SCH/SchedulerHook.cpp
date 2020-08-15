#include "Scheduler.h"

#include "Button.h"
#include "MotorController.h"

void sch_initilize_hook() {
    button_initialize();
    motorcontroller_initilze();
}