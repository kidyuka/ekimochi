#include "MotorController.h"
#include "Util.h"

/**
 * Define the connection ports of the gyro sensor and motors.
 * By default, the Gyro Boy robot uses the following ports:
 * Left motor:  Port C
 * Right motor: Port B
 */
static const motor_port_t left_motor = EV3_PORT_C, right_motor = EV3_PORT_B;

#define white 40
#define black 20

void motorcontroller_task(intptr_t exinf) {

    static float lasterror = 0, integral = 0;
    static float midpoint = (white - black) / 2 + black;
    static uint32_t count = 0;

    float error = midpoint - ev3_color_sensor_get_reflect(EV3_PORT_1);
    integral = error + integral * 0.05;
    float steer = 0.7 * error + 0.1 * integral + 1 * (error - lasterror);
    ev3_motor_steer(left_motor, right_motor, 75, steer * 3.0);
    
    lasterror = error;

    if(count++ % 10 == 0) {
        syslog_printf(LOG_NOTICE, "error: %f, steer: %f", error, steer);
    }
    //tslp_tsk(100000); /* 100msec */
}

void motorcontroller_initilze() {
    ev3_sensor_config(EV3_PORT_1, COLOR_SENSOR);
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);
    
    syslog(LOG_NOTICE, "#### motor control start");
    sta_cyc(MOTORCONTROLLER_TASK);
}
