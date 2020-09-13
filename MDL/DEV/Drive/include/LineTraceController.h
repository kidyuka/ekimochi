/**
 * @file LineTraceController.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
 */

#ifndef LINETRACECONTROLLER_H
#define LINETRACECONTROLLER_H

#include "ev3api.h"

#ifdef __cplusplus

#include "DriveController.h"

class LineTraceController {
private:
    bool  mRequested;
    float mTargetValue;
    float mDeviation;
    float mIntegral;
    float mOutput;

    const float mKP;
    const float mKI;
    const float mKD;
    const float mDISCOUNT;

public:
    LineTraceController(float KP, float KI, float KD, float I_DISCOUNT);

    // @brief 制御を開始する。
    bool start();

    // @brief モータの回転を即座に止めるか、惰性で回転させるままにするかを指定
    bool stop();

    // ライントレースタスクの本体
    void runTask();
};

extern LineTraceController gLineTraceController;

#endif // __cplusplus
#endif // LINETRACECONTROLLER_H