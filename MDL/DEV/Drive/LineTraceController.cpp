#include "DriveController.h"
#include "LineTraceController.h"
#include "cfg/DriveController_cfg.h"
#include "Util.h"

#define R_RATE  3
#define L_RATE  2.5

bool LineTraceController::mRequested = false;

void LineTraceController::runTask() {
    float P, I, D;

    // ライントレース制御に要求が無ければ、何もしない。
    if(mRequested == false)
        return;

    P = mTargetValue - ev3_color_sensor_get_reflect(EV3_PORT_1);
    I = mIntegral + P;
    D = P - mDeviation;

    mDeviation = P;
    mIntegral  = I;
    mOutput += (LINETRACE_PID_KP * P) + (LINETRACE_PID_KI * I) + (LINETRACE_PID_KD * D);

    if(mOutput > PWM_MAX) {
        mOutput = PWM_MAX;
    } else if(mOutput < PWM_MIN) {
        mOutput = PWM_MIN;
    }
    
    gDriveController.setSteer((int)mOutput);
}

#if 0
void LineTraceController::runTask()  {

    float lasterror = 0, integral = 0;
    float midpoint = 19;
    uint32_t count = 0;
    uint8_t sensor;

    // ライントレース制御に要求が無ければ、何もしない。
    if(mRequested == false)
        return;

    mDeviation = mTargetValue - ev3_color_sensor_get_reflect(EV3_PORT_1);
    integral = mDeviation * 0.5;
    while(linetrace_requested) {
        sensor = ev3_color_sensor_get_reflect(EV3_PORT_1);
        float error = midpoint - sensor;
        integral = error * 0.5 + integral * 0.5;
        float steer = error * 0.2 + integral + (error - lasterror) * 1.5;
        float rate; // = (100.0 - fabs(steer)*RATE) / 100.0;

        if(steer > 0.00) {
            rate = (100.0 - fabs(steer) * R_RATE) / 100.0;
            gLeftMotor.setTargetSpeed(linetrace_requested_speed);
            gRightMotor.setTargetSpeed(linetrace_requested_speed * rate);
        } else {
            rate = (100.0 - fabs(steer) * L_RATE) / 100.0;
            gLeftMotor.setTargetSpeed(linetrace_requested_speed * rate);
            gRightMotor.setTargetSpeed(linetrace_requested_speed);
        }

        lasterror = error;
        tslp_tsk(100 * 1000); /* 100msec */
        if(count++ % 10 == 0) {
            syslog_printf(LOG_NOTICE, 
                "sesor: %d, error: %f, steer: %f, r: %f",
                sensor, error, steer, rate);
        }
    }
}
#endif

LineTraceController::LineTraceController() {
    mRequested = false;
}

bool LineTraceController::start() {
    mRequested = true;
    // 課題 カラーセンサーのキャリブレーション結果を反映する
    // そもそも黒以外の色にも対応させる必要がある。
    mTargetValue = 19;
    mDeviation = 0;
    mIntegral = 0;
    mOutput = 0;

    gDriveController.start();
    return true;
}

bool LineTraceController::stop(bool motor_brake) {
    mRequested = true;
    gDriveController.stop(motor_brake);
    return true;
}

void LineTraceController::setSpeed(int speed) {
    mRequested = true;
    gDriveController.setSpeed(speed);
    return;
}
