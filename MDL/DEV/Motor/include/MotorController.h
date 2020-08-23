#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void	motorcontroller_task(intptr_t exinf);

#ifdef __cplusplus
}

extern void motorcontroller_initilze() ;

class MotorController {
private:
    motor_port_t mPort;
    bool    mReqBrake;
    int32_t mTargetSpeed;
    int32_t mSpeed;
    int32_t mPrevCount;
    SYSTIM  mPrevTime;
    bool    mRunning;
    
    float mDeviation;
    float mIntegral;
    float mOutput;
    
    void controlPWM(int32_t nowSpeed) ;

public:
    MotorController(motor_port_t port);
    ~MotorController();

    void initilize();
    void runTask();
    void debug();
    
    /**
     * @fn     現在のモータ回転角を取得
     * @brief  要約説明
     * @return モータ回転カウント値
     */
    void getCount(int32_t* count, SYSTIM* time) {
        *count = mPrevCount;
        *time = mPrevTime;
    }

    /**
     * @fn モータ回転速度の目標値を設定
     * @brief 1秒あたりの回転角度を設定
     */
    void setTargetSpeed(uint32_t speed, bool brake = false) {
        mTargetSpeed = speed;
        mReqBrake = brake;
    }

    /**
     * @fn モータ回転速度の目標値を取得
     */
    int32_t getTargetSpeed() {
        return mTargetSpeed;
    }
};

extern MotorController gLeftMotor;
extern MotorController gRightMotor;

#endif // __cplusplus
#endif // MOTORCONTROLLER_H