/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DE40.c
 * Original SHA-256: 96dca523a38e3d6c0e8b30c1aa1b449b47c2bed21b6556c37ac1e427fa4872c5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Descriptor;

extern void func_0800C804(Descriptor *descriptor, u16 *destination, u8 mode);

/* 0800DE40..0800DE62: 34 bytes, 16 instructions. */
void func_0800DE40(Descriptor *descriptors, u16 *destination)
{
    u16 *values = destination;
    Descriptor *descriptor = descriptors;
    s32 index;

    for (index = 0; index < 4; index++) {
        func_0800C804(descriptor, values, 8);
        values++;
        descriptor++;
    }
}
