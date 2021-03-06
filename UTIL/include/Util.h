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
extern int32_t strcpy(char* dest, const char* src);

inline int32_t abs(int32_t value) {
    return (value > 0) ? value : -value;
}

inline float fabs(float value) {
    return (value > 0) ? value : -value;
}

inline int32_t sign(int32_t value) {
    return (value > 0) ? 1 : -1;
}

inline void memset(char* dest, int value, uint32_t size) {
    while(size--) {
        *dest++ = value;
    }
}

inline void memcpy(uint8_t* dest, const uint8_t* src, uint32_t size) {
    while(size--) {
        *dest++ = *src++;
    }
}

#define PI 3.1415926f

float sin(float rad);
float cos(float rad);
float sqrt(float val);
float getDistance(float rad);

#endif // UTIL_H