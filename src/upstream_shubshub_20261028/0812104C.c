/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812104C.c
 * Original SHA-256: 01c706f92f6818eff4e12791cd815f5e080938b7b00ac17c9a4c498c933595fb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct
{
    u16 state;
    u16 unknown_02;
    void *resource;
} Command;

typedef struct
{
    u8 unknown_00[6];
    u16 selection;
    u32 handle;
    void *resource;
} CommandState;

typedef struct
{
    u8 unknown_00[12];
    u16 flags;
    u8 unknown_0E[16];
    u16 value;
    u16 saved_value;
} ResourceEntry;

extern u16 data_03000000;
extern u8 func_080DD494(void *resource);
extern ResourceEntry *func_080DD4A4(void *resource, u8 index);
extern void *func_080A880C(void *resource);
extern u32 func_080D3508(u16 action, void *resource, u32 variant);
extern u32 func_080D3888(u32 handle);

static inline void select_input(CommandState *state)
{
    if (data_03000000 & 0x40)
        state->selection = 0x134;
    else if (data_03000000 & 0x20)
        state->selection = 0x133;
    else if (data_03000000 & 0x10)
        state->selection = 0x135;
    else if (data_03000000 & 0x80)
        state->selection = 0x136;
    else if (data_03000000 & 2)
        state->selection = 0x137;
}

/* Complete target: 0x0812104C..0x081211B8, 364 bytes. */
s32 func_0812104C(void *context, Command *command, CommandState *state)
{
    switch (command->state)
    {
    case 0:
    {
        u8 count;
        u8 index;

        state->resource = command->resource;
        count = func_080DD494(state->resource);
        for (index = 0; index < count; index++)
        {
            ResourceEntry *entry = func_080DD4A4(state->resource, index);
            entry->flags |= 2;
            entry->saved_value = entry->value;
        }
        state->selection = 0x137;
        break;
    }
    case 0x100:
        select_input(state);
        func_080A880C(state->resource);
        state->handle = func_080D3508(0x159, state->resource, state->selection);
        command->state++;
        break;
    case 0x101:
        select_input(state);
        state->handle = func_080D3888(state->handle);
        if (state->handle == 0)
        {
            state->handle = func_080D3508(state->selection, state->resource, 0);
            command->state++;
        }
        break;
    case 0x102:
        state->handle = func_080D3888(state->handle);
        if (state->handle == 0)
            command->state = 2;
        break;
    }
    return 0;
}
