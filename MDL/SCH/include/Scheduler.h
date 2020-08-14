#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void	scheduler_task(intptr_t exinf);

#ifdef __cplusplus
}
#endif

void scheduler_initilize_hook();

#endif // SCHEDULER_H