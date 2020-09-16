#include "ev3api.h"
#include "app.h"

#include "Scheduler.h"

void main_task(intptr_t unused) {
    scheduler_task();
}
