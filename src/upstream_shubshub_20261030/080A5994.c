/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080A5994.c
 * Original SHA-256: f5f2d2cafa69495ccdf969f5ea405b1494926eb0ae4474b7ae88f425ecdd05b7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} EffectObject;

typedef struct {
    EffectObject *object;
    u8 unknown_04[0x28];
} EffectEntry;

typedef struct {
    u8 unknown_00[0x20];
    EffectEntry entries[14];
    void *tasks[14];
    u8 count;
    u8 current;
} EffectSequence;

extern u8 func_080D3878(const void *task);
extern void func_080D3864(void *task);
extern void *func_080D3508(u16 resource, u32 mode, void *context);
extern u8 func_080A8858(const void *entry, u8 selector);

/* Complete 0x080A5994..0x080A5A7C: 232 bytes, 106 instructions. */
u32 func_080A5994(EffectSequence *state)
{
    if (state->current >= state->count)
        return 0;

    if (state->tasks[state->current] != 0) {
        if (func_080D3878(state->tasks[state->current])) {
            state->entries[state->current].object->flags |= 0x10;
            func_080D3864(state->tasks[state->current]);
            state->tasks[state->current] = 0;
            state->current++;
        }
    } else {
        while (state->current < state->count) {
            if (func_080A8858(&state->entries[state->current], 3)) {
                state->entries[state->current].object->flags |= 0x10;
                state->tasks[state->current] = func_080D3508(
                    0x15C, 0, state->entries[state->current].object);
                break;
            }
            state->current++;
        }
    }
    return 1;
}
