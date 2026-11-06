/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0813790C.c
 * Original SHA-256: 412fd69c599f684a74ac84f5a4300d09cbde622f80a193ba8654193019224e1e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u8 animation[0x4E];
    u16 brightness;
    u8 unknown_6C[4];
    u8 field_70;
    u8 field_71;
    u8 unknown_72;
    u8 active;
    u8 started;
    u8 unknown_75;
    u8 id;
    u8 unknown_77;
    u16 field_78;
    u16 lifetime;
    u16 interval;
    u16 speed;
    s16 offset;
    u16 x;
    u16 y;
    u8 unknown_86[2];
} Entry0813790C;

typedef struct {
    u8 phase;
    u8 unknown_01[3];
    Entry0813790C entries[6];
} State;

typedef struct {
    u8 unknown_00[0x2FC2];
    u8 variant : 2;
} Global;

extern u8 *data_0200F3B0;
extern u8 *data_083A8C54[];
extern Global g_state_02000000;
extern u16 func_08137A80(void *state);
extern void func_0813777C(void *animation, u8 palette,
                          void *first, void *second,
                          u32 duration, u32 forward);

/* Complete target: 0x0813790C..0x081379C8, 188 bytes. */
void func_0813790C(State *state)
{
    u16 duration;
    u32 direction;
    u8 i;

    for (i = 0; i < 6; i++) {
        if (state->entries[i].active == 1) {
            duration = func_08137A80(data_0200F3B0 + 0x8998) % 30U + 30;
            direction = (u16)func_08137A80(data_0200F3B0 + 0x8998);
            direction &= 1;
            func_0813777C(state->entries[i].animation, i + 10,
                           data_083A8C54[g_state_02000000.variant * 2 + 1] + 0x40,
                           data_083A8C54[g_state_02000000.variant * 2 + 1] + 0x1E0,
                           duration, direction);
        }
    }
}
