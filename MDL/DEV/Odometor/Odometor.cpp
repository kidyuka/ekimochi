#include "Odometor.h"
#include "cfg/Odometor_cfg.h"

#include "MotorController.h"
#include "Util.h"

Odometor gOdometor;

Odometor::Odometor() {
    mOdo.x = 0;
    mOdo.y = 0;
    mOdo.direction = PI / 2.0;
    gLeftMotor.getCount(&mLeft, &mOdo.time);
    gRightMotor.getCount(&mRight, &mOdo.time);
}

void Odometor::runTask() {
    int32_t left, right;
    int32_t diffL, diffR;
    float   forward;
    SYSTIM time;

    gLeftMotor.getCount(&left, &time);
    gRightMotor.getCount(&right,&time);

    diffL = left - mLeft;
    diffR = right - mRight;

    forward = (diffL + diffR) / 2.0;
    mOdo.x += forward * sin(mOdo.direction);
    mOdo.y += forward * cos(mOdo.direction);
    mOdo.direction += (diffR - diffL) / TREAD_SIZE;
}
