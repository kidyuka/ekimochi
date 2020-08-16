
#include "ev3api.h"
#include "app.h"

#include "Util.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

void main_task(intptr_t unused) {
    char* dest = (char*)(0x30000000);
    strcpy(dest, "hello world!");
}
