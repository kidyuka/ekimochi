#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void	device_task(intptr_t exinf);

extern void	device_sensor_task(intptr_t exinf);

extern void	device_controller_task(intptr_t exinf);

#ifdef __cplusplus
}

extern void device_controller_initilize();

extern void device_sensor_initilize();

extern void device_task_start();

#endif // __cplusplus
#endif // DEVICECONTROLLER_H