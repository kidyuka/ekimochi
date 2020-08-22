#include <stdarg.h>

#include "Util.h"

#define PRINTF_BUFFER_SIZE 200
static char print_buffer[PRINTF_BUFFER_SIZE];
    
void syslog_printf(uint32_t level, const char* format, ... ) {
    va_list args;

    va_start(args, format); 
    vsnprintf(print_buffer, sizeof(print_buffer), format, args);
    va_end(args); 
    
    syslog(level, print_buffer);
}

int32_t strcpy(char* dest, const char* src) {
    const char* org = src;
    while(*src != 0) {
        *dest++ = *src++;
    }
    return src - org;
}
