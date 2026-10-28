/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08066DC4.c
 * Original SHA-256: 063347a51b1270c92e968a0e658c0ed23ef9f4490cb6e3800987da690254e755
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 mode;
} Menu;

extern u8 func_080099A4(u8 mode);

/* Complete target: [0x08066DC4, 0x08066DDC), 24 bytes, 11 instructions. */
u32 func_08066DC4(Menu *menu)
{
    if (func_080099A4(menu->mode) != 0)
        return 1;
    return 0;
}
