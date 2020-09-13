#include "Device_Cfg.h"
#include "DriveController.h"
#include "cfg/DriveController_cfg.h"
#include "LineTraceController.h"

#include "MotorController.h"
#include "Util.h"

#define WHEEL_CIRCUMFERENCE ((float)WHEEL_SIZE * PI)
#define LEN2RAD(L) ((L) / WHEEL_CIRCUMFERENCE * 360.0)

DriveController gDriveController;

bool DriveController::mRequested = false;
int  DriveController::mReqTurn = 0;
bool DriveController::mReqBrake = false;
int  DriveController::mSpeed = 0;
int  DriveController::mSteer = DRIVECTL_STRAIGHT;

DriveController::DriveController() {
    mRequested = false;
}

void DriveController::runTask() {
    if(mRequested == false) {
        return ;
    }

    if(mSpeed == 0) {
        gLeftMotor.setTargetSpeed(0, mReqBrake);
        gRightMotor.setTargetSpeed(0, mReqBrake);

    } else if(mReqTurn != 0) {
        int rad = LEN2RAD(mSpeed);
        if(mReqTurn > 0) {
            gLeftMotor.setTargetSpeed(rad);
            gRightMotor.setTargetSpeed(-rad);
        } else {
            gLeftMotor.setTargetSpeed(-rad);
            gRightMotor.setTargetSpeed(rad);
        }

    } else if(mSteer == DRIVECTL_STRAIGHT) {
        int rad = LEN2RAD(mSpeed);
        gLeftMotor.setTargetSpeed(rad);
        gRightMotor.setTargetSpeed(rad);

    } else {
        int steer = abs(mSteer);
        float radSpeed = (float)mSpeed / (float)steer;
        #if 0
            if(steer < TREAD_SIZE/2) {
                //片側の車輪を固定して回転する要求だとみなす
                steer = TREAD_SIZE/2;
            }
            // 車軸中央の速度を維持するように制御
            int s1 = ((steer - TREAD_SIZE/2) * radSpeed) / WHEEL_CIRCUMFERENCE * 360;
            int s2 = ((steer + TREAD_SIZE/2) * radSpeed) / WHEEL_CIRCUMFERENCE * 360;
        #else
            if(steer < TREAD_SIZE) {
                //片側の車輪を固定して回転する要求だとみなす
                steer = TREAD_SIZE;
            }
            // カーブの外側の車輪の速度を維持するように制御（車体速度は減速することになる）
            int s1 = LEN2RAD((steer - TREAD_SIZE) * radSpeed);
            int s2 = LEN2RAD(mSpeed);
        #endif

        if(mSteer > 0) {
            gLeftMotor.setTargetSpeed(s2);
            gRightMotor.setTargetSpeed(s1);
        } else {
            gLeftMotor.setTargetSpeed(s1);
            gRightMotor.setTargetSpeed(s2);
        }
    }

    // 更新要求は完了した
    mRequested = false;
}

bool DriveController::start() {
    mRequested = true;
    return true;
}

bool DriveController::stop(bool motor_brake) {
    mRequested = true;
    mReqBrake = motor_brake;
    mReqTurn = 0;
    mSpeed = 0;
    return true;
}

void DriveController::setSpeed(int speed) {
    mSpeed = speed;
    mRequested = true;
}

#define STEER_RATE ((DRIVECTL_CURVE_MIN - DRIVECTL_CURVE_MAX) / 100)
void DriveController::setSteer(int steer) {
    if(steer > DRIVECTL_STEER_MAX) {
        steer = DRIVECTL_STEER_MAX;
    } else if(steer < DRIVECTL_STEER_MIN) {
        steer = DRIVECTL_STEER_MIN;
    }

    if(steer == 0) {
        setCurvature(DRIVECTL_STRAIGHT);
    } else {
        int s = DRIVECTL_CURVE_MAX + STEER_RATE * (100 - abs(steer));
        if(steer > 0) {
            setCurvature(s);
        } else {
            setCurvature(-s);
        }
    }
}

void DriveController::setCurvature(int steer) {
    mSteer = steer;
    mRequested = true;
}

void DriveController::reqTurn(int rad) {
    mReqTurn = rad;
    mSteer = 0;
    mRequested = true;
}