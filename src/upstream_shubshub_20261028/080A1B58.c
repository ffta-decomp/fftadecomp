/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A1B58.c
 * Original SHA-256: c926e9d7636da9ee7ab98a5b60927e41a6477f59f798b616e25b7db96cb5c907
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 z;
    u8 unknown_0E[0x46];
    void *child;
} Parent080A1B58;

typedef struct {
    Parent080A1B58 *parent;
    u8 first;
    u8 second;
    u8 unknown_06;
    u8 mode;
    u8 enabled;
    u8 unknown_09;
    u16 x;
    u16 y;
    u16 z;
    u8 active;
    u8 unknown_11[3];
} State080A1B58;

typedef void (*BufferInitializer080A1B58)(void *destination, u32 size);
typedef void (*ChildCallback080A1B58)(void *object, u8 value);

extern BufferInitializer080A1B58 const g_callbacks_0836D4B8[];
extern ChildCallback080A1B58 const data_08394054[];

/* Complete [0x080A1B58, 0x080A1BE8): 144 bytes, 64 instructions. */
void func_080A1B58(State080A1B58 *state, Parent080A1B58 *parent,
                   u16 x, u16 y, u16 z, u8 value)
{
    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->parent = parent;
    if ((s16)x >= 0 && (s16)y >= 0 && (s16)z >= 0) {
        state->x = x;
        state->y = y;
        state->z = z;
    } else {
        state->x = parent->x;
        state->y = parent->y + 0x30;
        state->z = parent->z;
    }
    state->first = value;
    state->active = 1;
    state->second = value;
    state->mode = 4;
    state->enabled = 1;
    data_08394054[0](parent->child, 1);
}
