/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A52D4.c
 * Original SHA-256: d9fb9fe305daab3325079b4767660b2de334df2caa39c87c9725815bbd35b4a6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0e[0xe];
    u8 flags;
} Object080A52D4;

typedef struct {
    u8 unknown_00[0x1c];
    Object080A52D4 *object;
    void *primary_task;
    void *secondary_task;
    u8 unknown_28[2];
    u16 type;
} Entry080A52D4;

typedef struct {
    u8 unknown_00[4];
    Entry080A52D4 entries[15];
    u8 unknown_298[0x28];
    u8 count;
} State080A52D4;

extern s32 func_0809C8C8(Object080A52D4 *object, s32 mode);
extern void func_080A92E4(s32 mode, s32 x, s32 height, s32 y, s32 effect);
extern void func_08141570(s32 group, s32 sound);
extern u8 func_0809D8B4(void *task);
extern void func_0809D8C4(void *task);
extern u8 func_080A7C9C(void *task);

/* Complete [0x080A52D4, 0x080A53E4): 272 bytes, 130 instructions. */
s32 func_080A52D4(State080A52D4 *state)
{
    s32 active = 0;
    s32 i;

    for (i = 0; i < state->count; i++) {
        if (state->entries[i].type == 2) {
            u8 old_flags = state->entries[i].object->flags;

            if (func_0809C8C8(state->entries[i].object, 3) == 1)
                active = 1;
            if (!(old_flags & 2) && (state->entries[i].object->flags & 2)) {
                s32 has_type_one;

                func_080A92E4(0, state->entries[i].object->x,
                              state->entries[i].object->height,
                              state->entries[i].object->y, 0x15);
                has_type_one = 0;
                for (i = 0; i < state->count; i++) {
                    if (state->entries[i].type == 1)
                        has_type_one = 1;
                }
                if (!has_type_one)
                    func_08141570(2, 0x8d);
            }
        }

        if (state->entries[i].primary_task) {
            if (!func_0809D8B4(state->entries[i].primary_task)) {
                func_0809D8C4(state->entries[i].primary_task);
                state->entries[i].primary_task = 0;
            }
            active = 1;
        } else if (state->entries[i].secondary_task &&
                   func_080A7C9C(state->entries[i].secondary_task)) {
            active = 1;
        }
    }
    return active;
}
