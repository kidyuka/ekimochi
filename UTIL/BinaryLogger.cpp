#ifdef MEMMAP_LOG

#include "Logger.h"
#include "Util.h"
#include <stdarg.h>

BinaryLogger::BinaryLogger(const char* logname, uint32_t addr, uint32_t size) {
    mHead = (uint32_t*)addr;
    *mHead = 0;
    mPtr  = (uint8_t*)addr;
    mPtr += 4;
    mSize = size;
    syslog_printf(LOG_NOTICE, "binary-log: %s: 0x%x(%d)", logname, addr, size);
}

BinaryLogger::~BinaryLogger() {
}

bool BinaryLogger::_write(const void* src, uint32_t size) {
    // バッファメモリの残量を計算
    int32_t rest = mSize - (mPtr - (uint8_t*)mHead) - size;
    if(rest < 0) {
        // バッファを使い切った
        return false;
    }
    
    // バッファ先頭に使用メモリ量を記録
    *mHead += size;

    memcpy(mPtr, (const uint8_t*)src, size);
    mPtr += size;

    return true;
}

#endif // MEMMAP_LOG
