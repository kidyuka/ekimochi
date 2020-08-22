#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void	colorsensor_task(intptr_t exinf);

#ifdef __cplusplus
}

extern void colorsensor_task_start() ;

#endif // __cplusplus
#endif // COLORSENSOR_H