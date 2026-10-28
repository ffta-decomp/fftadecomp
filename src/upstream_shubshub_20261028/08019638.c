/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019638.c
 * Original SHA-256: 575815a5a012da2db7a66b4e617a9d62374b5dc08c2e84b454668fe03e83fbf1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 flags;
} CountState;

extern CountState *g_state_020020D0;
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* 08019638..08019680: 72 bytes. */
u32 func_08019638(u8 *destination)
{
    CountState *state = g_state_020020D0;
    u8 *cursor = destination;
    s32 count = 0;
    s32 bit;

    for (bit = 0; bit < 16; bit++) {
        if ((state->flags >> bit) & 1)
            count++;
    }

    if (count < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, count);
    return 0;
}
