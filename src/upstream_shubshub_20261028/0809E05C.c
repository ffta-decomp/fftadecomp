/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809E05C.c
 * Original SHA-256: 23e360c1e492fc55abea89d64775bb3f3f43324dd6974de4bb7f62a35aeaa5c1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xd0];
    s16 readiness;
    u8 unknown_d2[2];
    s16 bonus;
    u8 unknown_d6[0x32];
} Entry0809E05C;

typedef struct {
    u8 unknown_00[0x104];
    u8 order;
} Actor0809E05C;

typedef struct {
    Actor0809E05C *actor;
    u8 unknown_04[0x20];
    s32 key;
} Object0809E05C;

typedef struct {
    s32 count;
    Entry0809E05C entries[13];
    Object0809E05C *objects[13];
    u8 unknown_da0[0x68];
    s8 priority[13];
    s8 priority_count;
} State0809E05C;

extern u8 func_080CD8B4(const void *entry);
extern s32 func_0812E368(const void *entry);
extern u8 func_080CD92C(const void *entry);
extern u8 func_080CDCEC(const void *entry);
extern void func_0809DF7C(State0809E05C *state);

/* Complete [0x0809E05C, 0x0809E1E0): 388 bytes, 175 instructions. */
s32 func_0809E05C(State0809E05C *state)
{
    s32 selected = 0;
    s32 i;
    s32 best;
    s32 j;

    state->priority_count = 0;
    i = 0;
    if (i < state->count) {
        s8 *priority_count = &state->priority_count;

        do {
            if (func_080CD8B4(&state->entries[i]) == 1 &&
                func_0812E368(&state->entries[i])) {
                state->priority[*priority_count] = i;
                (*priority_count)++;
            }
            i++;
        } while (i < state->count);
    }

    if (state->priority_count) {
        selected = state->priority[0];
        (state->entries + selected)->bonus = 0x1000;
    } else {
        for (;;) {
            for (i = 0; i < state->count; i++) {
                if (!func_080CD92C(&state->entries[i]) &&
                    func_0812E368(&state->entries[i]) &&
                    !func_080CDCEC(&state->entries[i]) &&
                    state->entries[i].readiness > 999)
                    goto ready;
            }
            func_0809DF7C(state);
        }

ready:
        best = -65536;
        for (j = 0; j < state->count; j++) {
            if (func_080CD92C(&state->entries[j]) ||
                !func_0812E368(&state->entries[j]) ||
                func_080CDCEC(&state->entries[j]))
                state->objects[j]->key = -100;
            else
                state->objects[j]->key = state->entries[j].readiness
                    + state->entries[j].bonus;

            state->objects[j]->key *= 256;
            state->objects[j]->key |= state->objects[j]->actor->order;
            if (best < state->objects[j]->key) {
                best = state->objects[j]->key;
                selected = j;
            }
        }
    }
    return selected;
}
