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
private:
    static bool mRequested;
    static int  mReqTurn;
    static bool mReqBrake;
    static int  mSpeed;
    static int  mSteer;
public:
    DriveController();

    // @brief 制御を開始する。
    bool start();

    // @brief モータの回転を即座に止めるか、惰性で回転させるままにするかを指定
    // @param motor_brake false:即時停止 true:惰性
    bool stop(bool motor_brake);

    // @brief 制御の基準速度を指定する。 
    // @param speed 1秒あたり進む距離をmmで指定
    void setSpeed(int speed) ;

    // @param steer 回転半径(mm)で指定。正で右曲がり、負で左曲がり
    void setSteer(int steer) ;

    // @param speed その場で回転するスピード
    void reqTurn(int speed);

    void runTask();
};

extern DriveController gDriveController;

#endif // __cplusplus
#endif // DRIVECONTROLLER_H