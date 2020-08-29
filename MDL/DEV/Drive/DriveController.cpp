#include "DriveController.h"
#include "cfg/DriveController_cfg.h"
#include "LineTraceController.h"

#include "MotorController.h"
#include "Util.h"

#define PI (3.14)
#define WHEEL_CIRCUMFERENCE ((float)WHEEL_SIZE * PI)

DriveController gDriveController;

bool DriveController::mRequested = false;
int  DriveController::mReqTurn = 0;
bool DriveController::mReqBrake = false;
int  DriveController::mSpeed = 0;
int  DriveController::mSteer = 0;

DriveController::DriveController() {
    mRequested = false;
}

void DriveController::runTask() {
    if(mRequested == false) {
        return ;
    }

    if(mReqBrake == true) {
        gLeftMotor.setTargetSpeed(0, true);
        gRightMotor.setTargetSpeed(0, true);

    } else if(mReqTurn != 0 ) {
        if(mReqTurn > 0) {
            gLeftMotor.setTargetSpeed(mSpeed);
            gRightMotor.setTargetSpeed(-mSpeed);
        } else {
            gLeftMotor.setTargetSpeed(-mSpeed);
            gRightMotor.setTargetSpeed(mSpeed);
        }     

    } else if(mSteer == DRIVECTL_STRAIGHT) {
        gLeftMotor.setTargetSpeed(mSpeed);
        gRightMotor.setTargetSpeed(mSpeed);

    } else {
        int steer = abs(mSteer);
        if(steer < TREAD_SIZE/2) {
            //片側の車輪を固定して回転する要求だとみなす
            steer = TREAD_SIZE/2;
        }

        float radSpeed = (float)mSpeed / (float)steer;
        int s1 = ((steer - TREAD_SIZE/2) * radSpeed) / WHEEL_CIRCUMFERENCE * 360;
        int s2 = ((steer + TREAD_SIZE/2) * radSpeed) / WHEEL_CIRCUMFERENCE * 360;
        
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
    mSteer = 0;
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