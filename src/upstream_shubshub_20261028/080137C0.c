/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080137C0.c
 * Original SHA-256: 75f818a999736cb108c567fa3be38d7728b0bcd02db84bc6c985c59a65b3b04c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct PaletteState080137C0 {
    u8 unknown_00[0xA];
    u8 mode;
} PaletteState080137C0;

extern u16 func_08013794(u8 selection);
extern u16 data_03003860[];
extern u16 data_0500018C;

/* Complete [0x080137C0, 0x080137FE): 62 bytes, 25 instructions. */
void func_080137C0(PaletteState080137C0 *state, u8 selection)
{
    if (selection) {
        state->mode = 3;
        if (selection <= 4) {
            u16 color = func_08013794(selection);
            data_03003860[0xC6] = color;
            data_0500018C = color;
        }
    } else {
        state->mode = 0;
    }
}
