#include "DriveController.h"
#include "LineTraceController.h"
#include "cfg/DriveController_cfg.h"

#include "MotorController.h"
#include "Util.h"

void linetrace_controller_task() {
#if 0
    float lasterror = 0, integral = 0;
    float midpoint = 19;
    uint32_t count = 0;
    uint8_t sensor;

    lasterror = ev3_color_sensor_get_reflect(EV3_PORT_1);
    integral = lasterror * 0.5;
    while(true) {
        sensor = ev3_color_sensor_get_reflect(EV3_PORT_1);
        float error = midpoint - sensor;
        integral = error * 0.5 + integral * 0.5;
        float steer = error * 0.2 + integral + (error - lasterror) * 1.5;
        float rate; // = (100.0 - fabs(steer)*RATE) / 100.0;

        if(steer > 0.00) {
            rate = (100.0 - fabs(steer) * R_RATE) / 100.0;
            gLeftMotor.setTargetSpeed(SPEED);
            gRightMotor.setTargetSpeed(SPEED * rate);
        } else {
            rate = (100.0 - fabs(steer) * L_RATE) / 100.0;
            gLeftMotor.setTargetSpeed(SPEED * rate);
            gRightMotor.setTargetSpeed(SPEED);
        }

        lasterror = error;
        tslp_tsk(100 * 1000); /* 100msec */
        if(count++ % 10 == 0) {
            syslog_printf(LOG_NOTICE, 
                "sesor: %d, error: %f, steer: %f, r: %f",
                sensor, error, steer, rate);
        }
    }
#endif
}

LineTraceController::LineTraceController() {
}

LineTraceController& LineTraceController::getInstance() {
    static LineTraceController obj;
    return obj;
}

bool LineTraceController::start() {

    return true;
}

bool LineTraceController::stop(bool motor_brake) {
    return true;
}

bool LineTraceController::setSpeed(int speed) {
    return true;
}
