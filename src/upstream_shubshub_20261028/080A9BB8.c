/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A9BB8.c
 * Original SHA-256: e40103be6fb9acd27a4f6c30655552400cc24846b175f93c7cba227dfc445496
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    const void *image;
    u8 unknown_04[0x28];
    u16 flags;
    u8 unknown_2E[0x0C];
    s16 first;
    s16 second;
    s16 x[3];
    s16 y[3];
    u16 angle[3];
    s16 timer[3];
} TimedImages;

extern void func_08001F34(const void *, s32, s32, u32, u32, u32,
                          u32, u32, u32, u32, u32);
extern void func_080018A0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, s16, s16, u16, u32);

/* 0x080A9BB8..0x080A9C7E: 198 bytes. */
void func_080A9BB8(TimedImages *state)
{
    s32 i;

    if (state->image != 0) {
        for (i = 0; i < 3; i++) {
            if (state->timer[i] > 0) {
                state->timer[i]--;
                if (!(state->flags & 1))
                    func_08001F34(state->image, state->x[i], state->y[i],
                                   0, 0, 0, 0, 0, 0, 0, 0);
                else
                    func_080018A0(state->image, state->x[i], state->y[i],
                                   0, 0, 0, state->first, 0, state->second,
                                   0x100, 0x100, state->angle[i], 0);
            }
        }
    }
}
