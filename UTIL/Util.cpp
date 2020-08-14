#include <stdarg.h>

#include "Util.h"

#define PRINTF_BUFFER_SIZE 200

void syslog_printf(uint32_t level, char* format, ... ) {
    char buffer[PRINTF_BUFFER_SIZE];
    va_list args;

    va_start(args, format); 
    vsnprintf(buffer, PRINTF_BUFFER_SIZE, format, args);
    va_end(args); 
    
    syslog(level, buffer);
}