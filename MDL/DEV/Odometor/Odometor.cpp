#include "Device_Cfg.h"
#include "Odometor.h"
#include "cfg/Odometor_cfg.h"

#include "MotorController.h"
#include "Util.h"

#define WHEEL_CIRCUMFERENCE ((float)WHEEL_SIZE * PI)
#define LEN2RAD(L) ((L) / WHEEL_CIRCUMFERENCE * 360.0)
#define RAD2LEN(R) ((R) / 360.0 * WHEEL_CIRCUMFERENCE)

Odometor gOdometor;

Odometor::Odometor() {
    mOdo.x = 0;
    mOdo.y = 0;
    mOdo.direction = 0;
    gLeftMotor.getCount(&mLeft, &mOdo.time);
    gRightMotor.getCount(&mRight, &mOdo.time);
}

void Odometor::runTask() {
    int32_t left, right;
    float   diffL, diffR;
    float   forward;

    gLeftMotor.getCount(&left, &mOdo.time);
    gRightMotor.getCount(&right,&mOdo.time);

    diffL = RAD2LEN(left - mLeft);
    diffR = RAD2LEN(right - mRight);

    forward = (diffL + diffR) / 2.0;
    mOdo.x += forward * cos(mOdo.direction);
    mOdo.y += forward * sin(mOdo.direction);
    mOdo.direction += (diffR - diffL) / TREAD_SIZE;

    mLeft = left;
    mRight = right;
}
