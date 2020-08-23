#include "DriveController.h"
#include "LineTraceController.h"
#include "cfg/DriveController_cfg.h"
#include "Util.h"

LineTraceController gLineTraceController;

void LineTraceController::runTask() {
    float P, I, D;
    int sensor;

    // ライントレース制御に要求が無ければ、何もしない。
    if(mRequested == false)
        return;

    sensor = ev3_color_sensor_get_reflect(EV3_PORT_1);
    P = mTargetValue - sensor;
    I = mIntegral * LINETRACE_PID_DISCOUNT + P * (1.0 - LINETRACE_PID_DISCOUNT);
    D = P - mDeviation;

    mDeviation = P;
    mIntegral  = I;
    mOutput = (LINETRACE_PID_KP * P) + (LINETRACE_PID_KI * I) + (LINETRACE_PID_KD * D);

    if(mOutput > DRIVECTL_STEER_MAX) {
        mOutput = DRIVECTL_STEER_MAX;
    } else if(mOutput < DRIVECTL_STEER_MIN) {
        mOutput = DRIVECTL_STEER_MIN;
    }
    
    gDriveController.setSteer(mOutput);

    static int count = 0;
#if 0
    if(count++ % 20 == 0)
    syslog_printf(LOG_NOTICE, 
        "error: %f, steer: %f",
        mDeviation, mOutput);
#endif
}

LineTraceController::LineTraceController() {
    mRequested = false;
}

bool LineTraceController::start() {
    mRequested = true;
    // 課題 カラーセンサーのキャリブレーション結果を反映する
    // そもそも黒以外の色にも対応させる必要がある。
    mTargetValue = 17;
    mDeviation = 0;
    mIntegral = 0;
    mOutput = 0;

    //gDriveController.start();
    return true;
}

bool LineTraceController::stop(bool motor_brake) {
    mRequested = false;
    gDriveController.stop(motor_brake);
    return true;
}

void LineTraceController::setSpeed(int speed) {
    mRequested = true;
    gDriveController.setSpeed(speed);
    return;
}
