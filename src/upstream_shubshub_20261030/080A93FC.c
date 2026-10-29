/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080A93FC.c
 * Original SHA-256: 595e8e64de86cf9307f1f173a0921d21d702d990c34200586b5482207531ab05
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 active;
    u8 unknown_02[0x2A];
} AnimationRecord080A93FC;

typedef struct {
    u8 unknown_00[0x70];
    AnimationRecord080A93FC records[32];
} AnimationGlobals080A93FC;

extern AnimationGlobals080A93FC data_0200F9E8;

/* 0x080A93FC .. 0x080A9420: 36 bytes, including literal pools. */
void func_080A93FC(void)
{
    AnimationGlobals080A93FC *state = &data_0200F9E8;
    u8 inactive = 0;
    int index;

    for (index = 31; index >= 0; index--)
        state->records[index].active = inactive;
}
