/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08062430.c
 * Original SHA-256: 5eb2c0c8c0726c420bfa85f00fd3d960c27fbd201be6664deec687bec5164f36
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08062430..0x08062548: 280 bytes. */
typedef struct {
    u16 unknown_00;
    u16 pressed;
} InputState;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[0x0C];
    u32 flags;
    u8 unknown_58[0x14];
    u8 first[0x60];
    u8 second[0x20];
} CommandState;

typedef struct {
    u8 unknown_00[2];
    u8 type;
    u8 unknown_03[0x11D];
    u16 status;
    u16 timer;
    u16 mode;
} MenuState;

extern InputState data_03000000;
extern CommandState *data_0200F450;
extern MenuState data_030028A0;
extern u8 func_080C72E4(void);
extern u8 func_080C72F8(void);
extern void func_080C73C4(void *first, void *second, u32 size, u32 mode);

void func_08062430(void)
{
    if (data_03000000.pressed & 2)
        data_0200F450->flags |= 0x80;
    if (!func_080C72E4()) {
        if ((data_0200F450->flags & 0x80) && data_030028A0.mode == 0x101) {
            CommandState *state = data_0200F450;

            state->flags &= ~0x80;
            state->current = 0x44;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x36;
        } else if (func_080C72F8() || data_030028A0.status ||
                   (data_030028A0.timer > 240 && data_030028A0.type != 3)) {
            CommandState *state = data_0200F450;

            state->flags &= ~0x80;
            state->current = 0x44;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x36;
        }
    } else {
        func_080C73C4(data_0200F450->first, data_0200F450->second, 0x20, 2);
        data_0200F450->current = 6;
    }
}
