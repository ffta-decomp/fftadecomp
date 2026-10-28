/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018ABC.c
 * Original SHA-256: f9aff16f1bc3adcf0579128568495678d8740f27351f938b1fcc418bca87dfc1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete target: [0x08018ABC, 0x08018C24), 360 bytes. */
u16 func_08018ABC(u8 *buffer, u32 value)
{
    u16 digit_base = 0x8118;
    u8 *output = buffer;
    u8 started = 0;
    u16 digit = 0;

    while (value >= 1000000) {
        value -= 1000000;
        digit++;
        started = 1;
    }
    if (digit != 0) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 100000) {
        value -= 100000;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 10000) {
        value -= 10000;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 1000) {
        value -= 1000;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 100) {
        value -= 100;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 10) {
        value -= 10;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = value;
    digit += digit_base;
    *output++ = digit >> 8;
    *output++ = digit;
    *output = 0;
    return output - buffer;
}
