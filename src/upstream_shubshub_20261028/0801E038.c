/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801E038.c
 * Original SHA-256: 8b5af488f813a1dbfd23f1613e046648b965be3a6a31c2815a51fda2a6d99f92
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_02008158[];
extern u8 data_0200815C[];

/* 0801E038..0801E098: 96 bytes, 43 instructions. */
void func_0801E038(u8 mode, u8 *first, u8 *second, u8 *third)
{
    const u8 *values;

    if (mode == 1 || mode == 3) {
        values = data_02008158;

        if (first)
            *first = values[0];
        if (second)
            *second = values[1];
        if (third)
            *third = values[2];
    }
    if (mode == 2 || mode == 3) {
        values = data_0200815C;

        if (first)
            *first = values[0];
        if (second)
            *second = values[1];
        if (third)
            *third = values[2];
    }
}
