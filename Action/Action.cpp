#include "Action.h"
#include "cfg/Action_cfg.h"

static Action* CurrentAction = NULL;

void action_task_start() {
    CurrentAction = NULL;
    act_tsk(ACTION_TASK);
}

void action_task(intptr_t exinf) {
    while(true) {
        if(CurrentAction != NULL) {
            CurrentAction->run();
            CurrentAction = NULL;
        } else {
            tslp_tsk(100 * 1000); /* マイクロ秒で指定 */
        }
    }
}

bool request_action(Action* action) {
    if(CurrentAction == NULL) {
        CurrentAction = action;
        return true;
    } else {
        return false;
    }
}

bool Action::run() {
    bool retval = init();
    if(retval == true) {
        retval = exec();
    }
    if(retval == true) {
        retval = last();
    }
    return retval;
}
