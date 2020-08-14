
#include "ev3api.h"
#include "app.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

void main_task(intptr_t unused) {
    while(true) {
       tslp_tsk(100000); /* 100msec */
    }
}
