/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080385A8.c
 * Original SHA-256: 5a9e80d3b5164e696762d8406fe4f7ca212be22bcb1d743581c7f0b88dff7e70
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry;

typedef struct {
    u8 unknown_00[0x2B08];
    SlotEntry entries[64];
} EntryState;

extern EntryState g_state_02000000;

/* Complete [0x080385A8, 0x080385E4): 60 bytes, 26 instructions. */
s32 func_080385A8(u16 value, s32 limit)
{
    s32 count = 0;
    s32 index = 0;
    u8 cleared = 0;
    EntryState *state = &g_state_02000000;

    for (; index < 64; index++) {
        if (state->entries[index].value == value) {
            state->entries[index].value = cleared;
            state->entries[index].count = cleared;
            count++;
            if (count >= limit)
                break;
        }
    }
    return count;
}
