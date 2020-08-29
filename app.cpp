
#include "ev3api.h"
#include "app.h"

#include "Util.h"
#include "Logger.h"
#include "Scheduler.h"
#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

void main_task(intptr_t unused) {
    scheduler_task();
}
