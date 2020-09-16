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
    mOdo.forward = 0;
    gLeftMotor.getCount(&mLeft, &mOdo.time);
    gRightMotor.getCount(&mRight, &mOdo.time);
}

void Odometor::runTask() {
    int32_t left, right;
    float   diffL, diffR;
    float   forward, direction;

    gLeftMotor.getCount(&left, &mOdo.time);
    gRightMotor.getCount(&right,&mOdo.time);

    diffL = RAD2LEN(left - mLeft);
    diffR = RAD2LEN(right - mRight);

    forward = (diffL + diffR) / 2.0;
    direction = (diffR - diffL) / TREAD_SIZE;
    mOdo.x += forward * cos(mOdo.direction);
    mOdo.y += forward * sin(mOdo.direction);
    mOdo.direction +=  direction ;
    mOdo.forward += forward;

    mLeft = left;
    mRight = right;
}

float get_distance(const OdoData* p1, const OdoData* p2) {
    float x = p2->x - p1->x;
    float y = p2->y - p2->y;
    return sqrt(x * x + y * y);
}