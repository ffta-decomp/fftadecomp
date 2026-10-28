/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DC34.c
 * Original SHA-256: 890c2d0bf2a0513461a581f19263097706f4a08219b0bf5b2fe658c2cdbc85e6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct RangeState {
    u8 unknown_00[0x178];
    u16 values[160];
} RangeState;

extern RangeState *func_0800C614(void *object);
extern void func_0800C64C(void *object);

/* 0800DC34..0800DC7C: 72 bytes, 34 instructions. */
void func_0800DC34(void *object, s16 start, u8 count, u16 value)
{
    RangeState *state;
    s32 position;
    s32 index;

    if (start >= 160)
        return;
    state = func_0800C614(object);
    position = start;
    for (index = 0; index < count; index++, position++) {
        if (position < 0)
            continue;
        if (position >= 160)
            break;
        state->values[position] = value;
    }
    func_0800C64C(object);
}
