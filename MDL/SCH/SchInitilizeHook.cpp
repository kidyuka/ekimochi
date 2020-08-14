#include "Scheduler.h"

#include "Button.h"
#include "MotorController.h"

void scheduler_initilize_hook() {
    button_initialize();
    motorcontroller_initilze();
}