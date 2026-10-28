/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813255C.c
 * Original SHA-256: 9c4a2e9560c4bdc27820fc9b22a13254a8a06ca5d7f7f3b7e92a026ed3c29a13
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813255C..0x081325FC: 160 bytes. */
typedef struct {
    void *source;
    u8 unknown_04[4];
    void *target;
    u8 unknown_0C[0x14];
    s16 amounts[3];
    u16 flags;
    u8 index;
} Transfer;

typedef struct {
    u8 unknown_00[0x1F64];
    u32 balance;
} GameState;

extern GameState g_state_02000000;
extern u8 func_08131BB8(void *entity);

void func_0813255C(Transfer *transfer)
{
    u16 blocked = transfer->flags & 0x10;

    if (!blocked) {
        s32 amount = transfer->amounts[transfer->index];

        if (amount < 0)
            amount = -amount;
        if (func_08131BB8(transfer->target) != func_08131BB8(transfer->source)) {
            if (func_08131BB8(transfer->target)) {
                GameState *state = &g_state_02000000;
                s32 remaining = state->balance - amount;

                if (remaining <= 0)
                    state->balance = 0;
                else
                    state->balance = remaining;
            }
            if (func_08131BB8(transfer->source)) {
                GameState *state = &g_state_02000000;

                state->balance += amount;
                if (state->balance >= 99999999)
                    state->balance = 99999999;
            }
        }
    }
}
