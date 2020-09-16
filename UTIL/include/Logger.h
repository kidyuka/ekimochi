#ifndef LOGGER_H
#define LOGGER_H

#include "ev3api.h"

#ifdef MEMMAP_LOG

class TextLogger {
private:
    char* mHead;
    char* mPtr;
    uint32_t mSize;
public:
    TextLogger(const char* logname, uint32_t addr, uint32_t size);
    ~TextLogger();

    bool write(const char* format, ...);
};

class BinaryLogger {
private:
    uint32_t* mHead;
    uint8_t*  mPtr;
    uint32_t  mSize;
protected:
    bool _write(const void* src, uint32_t size);
public:
    BinaryLogger(const char* logname, uint32_t addr, uint32_t size);
    ~BinaryLogger();
};

#define WRITE_LOG(logname, ...) logname.write(__VA_ARGS__)
#include "../cfg/logger_cfg.inc"

#else
#define WRITE_LOG(logname, ...)
#endif //MEMMAP_LOG

#endif