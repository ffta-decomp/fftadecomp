/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9BCC.c
 * Original SHA-256: de67cd5358844a40ac7b93da0ba2ac186fb137baa8818c23d05eb4f68d14f0b0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D9BCC..0x080D9C46: 122 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    u32 value;
    u8 unknown_08[12];
    u16 palette_offset;
} PaletteCommand;

typedef struct {
    u8 active;
    u8 unknown_01[3];
    u32 handle;
    u16 palette_offset;
    u16 unknown_0A;
    u32 value;
} PaletteCommandState;

typedef void (*PaletteCallback)(u32 handle);
extern void func_080D9C48(u32 handle);
extern u32 func_0800C3CC(PaletteCallback callback, u32 size, u32 type,
                         u16 *palette);
extern u32 *func_0800C614(u32 handle);
extern void func_0800C668(u32 handle);
extern void func_0800C6C0(u32 handle);

u32 func_080D9BCC(void *context, PaletteCommand *command,
                  PaletteCommandState *state)
{
    switch (command->state) {
    case 0: {
        u16 *palette;

        state->palette_offset = command->palette_offset;
        state->value = command->value;
        palette = (u16 *)0x05000000 + state->palette_offset;
        state->handle = func_0800C3CC(func_080D9C48, 4, 2, palette);
        *func_0800C614(state->handle) = state->value;
        break;
    }
    case 1:
        func_0800C668(state->handle);
        break;
    case 0x100:
        if (state->active) {
            func_0800C6C0(state->handle);
            command->state++;
        }
        break;
    case 0x101:
        command->state = 2;
        break;
    }
    return 0;
}
