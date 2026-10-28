/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0814278C.c
 * Original SHA-256: e0340cf77ecab0272633a3a25045a5ffc94407986eebd2dfc7544f22b55dcba3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x0814278C..0x08142862: 214 bytes. */
#include "ffta.h"

typedef signed long long s64;
typedef unsigned long long u64;

s64 func_0814278C(double value)
{
    double high;
    u64 result;

    if (value < 0)
        return 0;

    high = value / ((u64)1 << 32);
    result = (u32)high;
    result <<= 32;
    value -= (double)result;

    if (value < 0)
        result -= (u32)(-value);
    else
        result += (u32)value;
    return result;
}
