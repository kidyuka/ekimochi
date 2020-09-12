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

#define TABLESIZE 128 //2の乗数であること
#define SUBBIT    8
#define SUBINDEX  (1 << SUBBIT)
#define I_PI      (TABLESIZE * SUBINDEX * 2)
#define I_HPI     (TABLESIZE * SUBINDEX)
#define NUM     8

//int(sin(index / (pi / 2) * 128) * 65535 + 0.5)
const unsigned short sin_table[] = {
    0,   804,  1608,  2412,  3216,  4019,  4821,  5623,
 6424,  7223,  8022,  8820,  9616, 10411, 11204, 11996,
12785, 13573, 14359, 15142, 15924, 16703, 17479, 18253,
19024, 19792, 20557, 21319, 22078, 22834, 23586, 24334,
25079, 25820, 26557, 27291, 28020, 28745, 29465, 30181,
30893, 31600, 32302, 32999, 33692, 34379, 35061, 35738,
36409, 37075, 37736, 38390, 39039, 39682, 40319, 40950,
41575, 42194, 42806, 43411, 44011, 44603, 45189, 45768,
46340, 46905, 47464, 48014, 48558, 49095, 49624, 50145,
50659, 51166, 51664, 52155, 52638, 53113, 53580, 54039,
54490, 54933, 55367, 55794, 56211, 56620, 57021, 57413,
57797, 58171, 58537, 58895, 59243, 59582, 59913, 60234,
60546, 60850, 61144, 61429, 61704, 61970, 62227, 62475,
62713, 62942, 63161, 63371, 63571, 63762, 63943, 64114,
64276, 64428, 64570, 64703, 64826, 64939, 65042, 65136,
65219, 65293, 65357, 65412, 65456, 65491, 65515, 65530,
65535, 0
};

float sin(float x)
{
    long ix, subix, sign, tval;

    ix = (int)(x * (I_PI / PI));   //単位変換
    sign = ix & I_PI;              //第3,第4象限である
    ix &= (I_PI - 1);              //第1,第2象限に限定
    if(ix > I_HPI) ix = I_PI - ix; //第1象限に限定

    subix = ix & (SUBINDEX - 1);   //線形補完に用いるサブインデックス
    ix >>= SUBBIT;                 //テーブル番号に変換

    //線形補完
    tval = ((long)sin_table[ix]   * (SUBINDEX - subix)
          + (long)sin_table[ix+1] * subix);

    return (sign ? -tval : tval) / (SUBINDEX * 65535.f);
}

float cos(float x)
{
    return sin(x+PI/2.);
}