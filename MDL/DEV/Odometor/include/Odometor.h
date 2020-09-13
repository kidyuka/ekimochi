/**
 * @file ODOMETOR.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
 */

#ifndef ODOMETOR_H
#define ODOMETOR_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}

struct OdoInfo {
    float  x;
    float  y;
    float  direction;
    SYSTIM time;
};

class Odometor {
private:
    int32_t mLeft;
    int32_t mRight;
    OdoInfo mOdo;

public:
    Odometor();

    void get(OdoInfo* info) {
        *info = mOdo;
    }
    
    void runTask();
};

extern Odometor gOdometor;

#endif // __cplusplus
#endif // ODOMETOR_H