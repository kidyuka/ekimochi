#include "DriveController.h"
#include "LineTraceController.h"
#include "cfg/DriveController_cfg.h"
#include "Util.h"

// 直線・カーブ 両方に対応のライントレーサー
LineTraceController gLineTraceController(
    LINETRACE_PID_KP,LINETRACE_PID_KI,LINETRACE_PID_KD,LINETRACE_PID_DISCOUNT
);

void LineTraceController::runTask() {
    float P, I, D;
    int sensor;

    // ライントレース制御に要求が無ければ、何もしない。
    if(mRequested == false)
        return;

    sensor = ev3_color_sensor_get_reflect(EV3_PORT_1);
    P = mTargetValue - sensor;
    I = mIntegral * mDISCOUNT + P * (1.0 - mDISCOUNT);
    D = P - mDeviation;

    mDeviation = P;
    mIntegral  = I;
    mOutput = (mKP * P) + (mKI * I) + (mKD * D);

    if(mOutput > DRIVECTL_STEER_MAX) {
        mOutput = DRIVECTL_STEER_MAX;
    } else if(mOutput < DRIVECTL_STEER_MIN) {
        mOutput = DRIVECTL_STEER_MIN;
    }
    
    gDriveController.setSteer(mOutput);
#if 0
    static int count = 0;
    if(count++ % 20 == 0)
    syslog_printf(LOG_NOTICE, 
        "error: %f, steer: %f",
        mDeviation, mOutput);
#endif
}

LineTraceController::LineTraceController(float KP, float KI, float KD, float I_DISCOUNT)
    : mKP(KP), mKI(KI), mKD(KD), mDISCOUNT(I_DISCOUNT)
{
    mRequested = false;
}

bool LineTraceController::start() {
    mRequested = true;
    // 課題 カラーセンサーのキャリブレーション結果を反映する
    // そもそも黒以外の色にも対応させる必要がある。
    mTargetValue = 20;
    mDeviation = 0;
    mIntegral = 0;
    mOutput = 0;

    return true;
}

bool LineTraceController::stop() {
    mRequested = false;
    return true;
}
