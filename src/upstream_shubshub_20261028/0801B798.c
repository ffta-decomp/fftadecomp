/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801B798.c
 * Original SHA-256: 996c9da65a48eae69ad53bf271043c71fd4c9b63ccbd6937255f515fdf3a2626
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Rectangle {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} Rectangle;

typedef struct DrawingState {
    u8 unknown_00[0x1E];
    u16 fill;
} DrawingState;

extern DrawingState g_state_02007F40;
extern u16 *func_0801AD1C(u8 layer);

/* 0801B798..0801B7F6: 94 bytes, 43 instructions. */
void func_0801B798(const Rectangle *rectangle, u8 layer)
{
    u16 fill = g_state_02007F40.fill;
    u16 *tiles = func_0801AD1C(layer);
    u8 x;
    u8 y;

    for (y = rectangle->top; y < rectangle->bottom && y < 64; y++) {
        for (x = rectangle->left; x < rectangle->right && x < 64; x++) {
            u16 *tile = tiles + (y * 64 + x);

            *tile = fill;
        }
    }
}
