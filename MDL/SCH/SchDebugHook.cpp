#include "Scheduler.h"
#include "Util.h"
#include "Logger.h"

#include "MotorController.h"
#include "Odometor.h"

void scheduler_debug_10sec_hook() {
}

void scheduler_debug_5sec_hook() {
}

void scheduler_debug_1sec_hook() {
    gLeftMotor.debug();
    gRightMotor.debug();
}

void scheduler_debug_100ms_hook() {
    OdoData info;
    gOdometor.get(&info);
    WRITE_LOG(OdoLog, info.x, info.y, info.direction, info.time);
}
