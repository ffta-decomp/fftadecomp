/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DFDC.c
 * Original SHA-256: 5886b455b902c12e38ed53ff4798924fe3a075ef206aab88dcbb150f0895b496
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_02008158[];
extern u8 data_0200815C[];

/* Complete target: 0x0801DFDC..0x0801E038, 92 bytes. */
void func_0801DFDC(u8 mode, u8 first, u8 second, u8 third)
{
    u8 *values;

    if (mode == 1 || mode == 3) {
        values = data_02008158;

        if (first)
            values[0] = first;
        if (second)
            values[1] = second;
        if (third)
            values[2] = third;
    }
    if (mode == 2 || mode == 3) {
        values = data_0200815C;

        if (first)
            values[0] = first;
        if (second)
            values[1] = second;
        if (third)
            values[2] = third;
    }
}
