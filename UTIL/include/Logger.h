#ifndef LOGGER_H
#define LOGGER_H

#include "ev3api.h"

class TextLogger {
private:
    char* mHead;
    char* mPtr;
    uint32_t mSize;
public:
    TextLogger(uint32_t addr, uint32_t size);
    ~TextLogger();

    bool write(const char* format, ...);
};

class BinaryLogger {
private:
    char* mHead;
    char* mPtr;
    uint32_t mSize;
public:
    BinaryLogger(uint32_t addr, uint32_t size, uint32_t unit_size);
    ~BinaryLogger();

    bool write(const char* src);
};

#include "../cfg/logger_cfg.h"

#endif