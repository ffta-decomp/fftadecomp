/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812E4F4.c
 * Original SHA-256: a1ae5e844f0ca5e0c1eaf68843f98a713bf42c6703ebef0c6c1be26a79b4303e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0812E4F4..0x0812E55C: 104 bytes. */
extern u32 func_080C7EA4(const void *, u8);
extern u32 func_080CA7A4(u16, u8);

u32 func_0812E4F4(const void *unit, u16 *output)
{
    int i;
    u32 count;

    output[0] = 0;
    output[1] = 0;
    i = 0;
    count = 0;
    for (; i < 5; ++i) {
        u32 entry = func_080C7EA4(unit, i + 0x1D);

        if (entry != 0) {
            switch (func_080CA7A4(entry, 6)) {
            case 1:
            case 2:
                if (func_080CA7A4(entry, 3) != 20) {
                    *output++ = entry;
                    ++count;
                }
                break;
            }
        }
    }
    return count;
}
