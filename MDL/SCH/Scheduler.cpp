#include "Scheduler.h"

void scheduler_task() {
    sch_initilize_hook();
    act_tsk(SCH_DEBUG_TASK);
}

void scheduler_debug_task(intptr_t exinf) {
    uint32_t count = 0;
    while(true) {
        scheduler_debug_100ms_hook();

        if(count % 10 == 0) {
            scheduler_debug_1sec_hook();
        }

        if(count % 50 == 0) {
            scheduler_debug_5sec_hook();
        }

        if(count % 100 == 0) {
            scheduler_debug_10sec_hook();
        }

        tslp_tsk(100000); // 100ms
        count ++;
    }
}