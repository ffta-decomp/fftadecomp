/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08063660.c
 * Original SHA-256: 86df2fe6145f47836664d6a2c8fab14174c8ad9c81e44e1ae2cb8da8391e6131
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08063660..0x0806379E: 318 bytes. */
typedef void (*CommandCallback)(s32 value);

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[5];
    u8 marker;
    u16 mode;
    u8 unknown_50[4];
    u32 flags;
    s32 previous;
    s32 selection;
    u8 unknown_60[4];
    u16 field_64;
    u16 field_66;
    u8 unknown_68[0x84];
    CommandCallback callback;
    u8 unknown_f0[0x798];
    u32 record;
} CommandState;

typedef struct {
    u32 first;
    s32 second;
} CommandRecord;

typedef struct {
    u8 unknown_00[0x1F64];
    u32 balance;
} GameState;

extern CommandState *data_0200F450;
extern CommandRecord g_state_020020D0;
extern GameState g_state_02000000;
extern void func_08061E70(s32 value);
extern void func_08066120(u8 marker);

void func_08063660(void)
{
    g_state_020020D0.first = data_0200F450->record;
    if (data_0200F450->selection != -1 && data_0200F450->previous != -1) {
        CommandState *state;

        g_state_020020D0.second = data_0200F450->previous;
        func_08061E70(0);
        data_0200F450->callback = func_08061E70;
        func_08066120(data_0200F450->marker);
        state = data_0200F450;
        state->mode = 0xBC;
        state->field_64 = 0x9001;
        state->field_66 = 0x1234;
        state->current = 0x1D;
        state->entries[state->count++] = state->current;
        state->current = 0x3C;
        state->entries[state->count++] = state->current;
        state->current = 0x39;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x35;
    } else {
        CommandState *state;

        if (data_0200F450->flags & 0x40) {
            g_state_02000000.balance += 5000;
            data_0200F450->flags &= ~0x40;
        }
        if (data_0200F450->selection == -1)
            data_0200F450->mode = 0xC8;
        else
            data_0200F450->mode = 0xC7;
        state = data_0200F450;
        state->current = 0x1C;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x35;
    }
}
