/**
 * @file DRIVECONTROLLER.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
 */

#ifndef LINETRACECONTROLLER_H
#define LINETRACECONTROLLER_H

#include "ev3api.h"

#ifdef __cplusplus

#include "DriveController.h"

// ライントレース処理の定期処理関数
void linetrace_controller_task();

class LineTraceController : public DriveController {
private:
    LineTraceController();
public:
    static LineTraceController& getInstance() ;

    bool start();
    bool stop(bool motor_brake);
    bool setSpeed(int speed);
};


#endif // __cplusplus
#endif // LINETRACECONTROLLER_H