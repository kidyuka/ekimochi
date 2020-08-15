#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void scheduler_task(intptr_t exinf);
extern void scheduler_debug_task(intptr_t exinf);

#ifdef __cplusplus
}

extern void sch_initilize_hook();
extern void scheduler_debug_10sec_hook();
extern void scheduler_debug_5sec_hook();
extern void scheduler_debug_1sec_hook();
extern void scheduler_debug_100ms_hook();

#endif // __cplusplus
#endif // SCHEDULER_H