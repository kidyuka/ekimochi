#include "MotorController.h"
#include "Util.h"
#include "Logger.h"

#define PWM_MAX 100
#define PWM_MIN -100
#define SPEED_CONTROL_INTERVAL (25)
#define MOTOR_PID_KP 0.15
#define MOTOR_PID_KI 0.00
#define MOTOR_PID_KD 0.00
#define MOTOR_INIT_PWM 20
#define MOTOR_DESCOUT 0.5

/**
 * Define the connection ports of the gyro sensor and motors.
 * By default, the Gyro Boy robot uses the following ports:
 * Left motor:  Port C
 * Right motor: Port B
 */
MotorController gLeftMotor(EV3_PORT_C);
MotorController gRightMotor(EV3_PORT_B);

void motorcontroller_task(intptr_t exinf) {
    while(true) {
        //gLeftMotor.runTask();
        //gRightMotor.runTask();
        tslp_tsk(SPEED_CONTROL_INTERVAL * 1000); /* マイクロ秒で指定 */
    }
}

void motorcontroller_initilze() {
    ev3_sensor_config(EV3_PORT_1, COLOR_SENSOR);
    
    gLeftMotor.initilize();
    gRightMotor.initilize();

    //act_tsk(MOTORCONTROLLER_TASK);
}

MotorController::MotorController(motor_port_t port) {
    mPort = port;
}

MotorController::~MotorController() {
}

void MotorController::initilize() {
    ev3_motor_config(mPort, LARGE_MOTOR);
    mTargetSpeed = mSpeed = 0;
    mPrevCount = ev3_motor_get_counts(mPort);
    get_tim(&mPrevTime);
    ev3_motor_stop(mPort, false);
    mRunning = false;
    mOutput = 0;
    mReqBrake = false;
}

void MotorController::debug() {
    DebugLog.write(
        "Port: %d, TargetSpeed: %d, Speed: %d, PWM: %f\n",
        mPort, mTargetSpeed, mSpeed, mOutput);
}

void MotorController::runTask() {
    int32_t count;
    float   elapsed;
    int32_t variation;
    SYSTIM  now;

    // 現在のモータ回転角を得る
    count = ev3_motor_get_counts(mPort);
    // 現在時間を得る
    get_tim(&now);

    if(mTargetSpeed == 0) {
        // 速度0 が要求値の場合はモータを停止
        if(mRunning) {
            ev3_motor_stop(mPort, mReqBrake);
            mRunning = false;
            mReqBrake = false;
        }
    } else if(mRunning == false) {
        // モータをまだ動かしていない場合は、初速設定に基づいてPWM値を設定
        // (下記の出力PWM値の調整処理が、モータが動いていることを前提としているため)
        mOutput = sign(mTargetSpeed) * MOTOR_INIT_PWM;
        ev3_motor_set_power(mPort, mOutput);
        mRunning = true;

    } else {
        if(count != mPrevCount) {
            // モータ角の現在値と前回値の差を得る
            variation = count - mPrevCount;
            // 前回と現在の経過時間(秒)を得る (get_tim は第3世代ではマイクロ秒で得られる)
            elapsed = (float)(now - mPrevTime) / (1000 * 1000);
            // 回転速度を得る(1秒あたりに変換)
            mSpeed = (float)variation / elapsed;
            // 目標値との差でPWM値を変更
            this->controlPWM(mTargetSpeed - mSpeed);
        } else {
            // モータ角位置が前回取得値から変化していない場合、
            // 回転速度を計算できないため、何も処理しない。
        }
    }

    mPrevCount = count;
    mPrevTime  = now;
}

void MotorController::controlPWM(int32_t deviation) {
    float P, I, D;
    
    P = deviation;
    I = mIntegral * MOTOR_DESCOUT + P * (1.0 - MOTOR_DESCOUT);
    D = P - mDeviation;

    mDeviation = P;
    mIntegral  = I;
    mOutput += (MOTOR_PID_KP * P) + (MOTOR_PID_KI * I) + (MOTOR_PID_KD * D);

    if(mOutput > PWM_MAX) {
        mOutput = PWM_MAX;
    } else if(mOutput < PWM_MIN) {
        mOutput = PWM_MIN;
    }
    ev3_motor_set_power(mPort, mOutput);
}
