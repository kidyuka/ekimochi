#ifdef MEMMAP_LOG

#include "Logger.h"
#include "Util.h"
#include <stdarg.h>

TextLogger::TextLogger(const char* logname, uint32_t addr, uint32_t size) {
    mPtr = mHead = (char*)addr;
    mSize = size;
}

TextLogger::~TextLogger() {
}

bool TextLogger::write(const char* format, ...) {
    va_list args;
    // バッファメモリの残量を計算
    int32_t rest = mSize - (mPtr - mHead);
    int32_t count;

    va_start(args, format);
    // 直接バッファメモリへ書き出し、戻り値の書き込みバイト数を得る
    count = vsnprintf(mPtr, rest, format, args);
    va_end(args);

    // 書き込みバイト数をポインタへ反映する
    mPtr += count;

    // バッファ残量があるならTrue
    return (mHead + mSize > mPtr);
}

#endif // MEMMAP_LOG
