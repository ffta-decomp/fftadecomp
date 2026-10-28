/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809D5E8.c
 * Original SHA-256: 0a0c0470c2839b1b9c5f1e0125e79454fc929150ec47d2351b2dcb376e387a0a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x29];
    u8 flags;
    u8 unknown_2A[0xB2];
    u16 counter;
} Object0809D5E8;

/* 0x0809D5E8..0x0809D612: 42 bytes, 21 instructions. */
void func_0809D5E8(Object0809D5E8 *object, u32 enabled)
{
    object->counter = 0;
    if (enabled == 0) {
        object->flags |= 1;
    } else {
        object->flags &= ~1;
    }
}
