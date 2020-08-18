
#include "ev3api.h"
#include "app.h"

#include "Util.h"
#include "Logger.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

void main_task(intptr_t unused) {
    DebugLog.write("hello world!\n");
}
