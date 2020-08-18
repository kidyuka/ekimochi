#include "Scheduler.h"

#include "Button.h"
#include "MotorController.h"
#include "Util.h"

void sch_initilize_hook() {
    button_initialize();
    motorcontroller_initilze();
}