#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void	devicecontroller_task(intptr_t exinf);

#ifdef __cplusplus
}

extern void devicecontroller_task_start() ;
extern void devicecontroller_initilize();

#endif // __cplusplus
#endif // DEVICECONTROLLER_H