/**
 * @file ACTION.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
 */

#ifndef ACTION_H
#define ACTION_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TOPPERS_MACRO_ONLY
extern void	action_task(intptr_t exinf);
#endif //TOPPERS_MACRO_ONLY

#ifdef __cplusplus
}

extern void action_task_start();

class Action {
public:
    virtual bool init() {return true;}
    virtual bool exec() = 0;
    virtual bool last() {return true;}
    bool run() ;
};

extern bool request_action(Action* action) ;

#endif // __cplusplus
#endif // ACTION_H