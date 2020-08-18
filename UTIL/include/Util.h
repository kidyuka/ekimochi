#ifndef UTIL_H
#define UTIL_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

extern void syslog_printf(uint32_t level, const char* format, ... );
extern int32_t abs(int32_t value);
extern float fabs(float value);
extern int32_t sign(int32_t value);
extern int32_t strcpy(char* dest, const char* src);
extern void memset(char* ptr, int value, uint32_t size) ;


#endif // UTIL_H