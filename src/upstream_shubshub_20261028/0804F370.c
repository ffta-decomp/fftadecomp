/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804F370.c
 * Original SHA-256: 2b198892da657fa75ce5f9fb65cca6676c19f5dba98a8c423b7cc87f7adb75f6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct DisplayLayout {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
} DisplayLayout;

typedef struct DisplayState {
    u8 unknown_00[8];
    u8 kind;
    u8 unknown_09[0x13];
    DisplayLayout layout;
} DisplayState;

extern const u8 data_083937CE[];
extern void func_08001F34(const void *descriptor, s32 x, s32 y,
                         u32 first, u32 second, u32 third, u32 fourth,
                         u32 fifth, u32 sixth, u32 seventh, u32 eighth);

/* 0804F370..0804F3B4: 68 bytes, 31 instructions. */
void func_0804F370(const DisplayState *state)
{
    const DisplayLayout *layout = &state->layout;

    if (state->kind == 4 || state->kind == 5)
        func_08001F34(data_083937CE, (layout->x + layout->width) * 8 - 40,
                     layout->y * 8 - 4, 0, 0, 0, 0, 0, 0, 0, 0);
}
