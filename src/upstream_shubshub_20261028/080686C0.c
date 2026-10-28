/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080686C0.c
 * Original SHA-256: 9ad71aa03b968c3c5b2e6425c51cbb0188f21df15f585c3afa9a0c1819920dbb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080686C0..0x080686F2: 50 bytes. */
typedef struct {
    u8 unknown_00[0x12];
    u8 stride;
} MenuControl;

typedef struct {
    u8 unknown_00[0x28];
    MenuControl control;
    u8 unknown_3c[0x84];
    u16 entries[1];
} MenuContext;

void func_080686C0(MenuContext *context)
{
    MenuControl *control = &context->control;
    s32 row = 0;
    s32 column;

    for (; row < 8; ++row)
        for (column = 0; column < 6; ++column)
            context->entries[(row + 1) * control->stride + column] = 0;
}
