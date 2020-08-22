/**
 * @file DRIVECONTROLLER.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
 */

#ifndef DRIVECONTROLLER_H
#define DRIVECONTROLLER_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TOPPERS_MACRO_ONLY
extern void	drivecontroller_task(intptr_t exinf);
#endif //TOPPERS_MACRO_ONLY

#ifdef __cplusplus
}

extern void drivecontroller_task_start();

class DriveController {
public:
    virtual bool start() = 0;
    virtual bool stop(bool motor_brake) = 0;
    virtual bool setSpeed(int speed) = 0;
};

#endif // __cplusplus
#endif // DRIVECONTROLLER_H