/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0809D2F8.c
 * Original SHA-256: 935f151a7f49c4ef71940649724aa41614e36219f8ab6e0550aaaeebc8931fcf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    void *object;
    void *resource;
    u8 unknown_08[0x64];
    u16 status;
    u8 unknown_6e[0x46];
} Entry0809D2F8;

typedef struct {
    u8 unknown_00[4];
    u8 flags;
    u8 unknown_05[3];
    Entry0809D2F8 entries[13];
} State0809D2F8;

extern u32 func_0809B88C(void *resource);
extern void func_08096F8C(void *object);
extern void func_08022854(void *resource);

static inline u8 entry_is_active(Entry0809D2F8 *entry)
{
    switch (entry->status) {
    case 0:
        return 0;
    case 1:
        if (func_0809B88C(entry->resource) == 0) {
            entry->status = 0;
            return 0;
        }
        return 1;
    default:
        return 1;
    }
}

/* Complete [0x0809D2F8, 0x0809D3A8): 176 bytes, 83 instructions. */
u8 func_0809D2F8(State0809D2F8 *state)
{
    u32 active = 0;
    s32 index;

    if (state->flags & 1) {
        for (index = 0; index <= 12; ++index) {
            if (state->entries[index].object) {
                u8 busy = entry_is_active(&state->entries[index]);

                if (busy == 0) {
                    func_08096F8C(state->entries[index].object);
                    state->entries[index].object = 0;
                } else {
                    active = 1;
                }
            }
        }
        if (active == 0) {
            state->flags &= ~1;
            for (index = 0; index <= 12; ++index) {
                if (state->entries[index].resource) {
                    func_08022854(state->entries[index].resource);
                    state->entries[index].resource = 0;
                }
            }
        }
    }
    return active;
}
