/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08025174.c
 * Original SHA-256: c9ed0de573095dcadec1110d021efcf670bf2443e3bffeb19bd1e67ccd554f14
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[9];
    u8 speed;
    u8 unknown_0A[0x16];
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} MoveState08025174;

extern u16 data_0200F3A4;
extern void func_0801E6F0(u16 *x, u16 *y);
/* The matched two-argument caller contract uses the observed first two words. */
extern void func_0801E5E0(u32 x, s16 y);

/* Complete target [0x08025174, 0x08025236): 194 bytes including literal pool. */
void func_08025174(MoveState08025174 *state)
{
    u16 *keys = &data_0200F3A4;
    u16 original_x, original_y;
    s16 x, y;

    func_0801E6F0(&original_x, &original_y);
    x = original_x;
    y = original_y;
    if (*keys & 0x20) {
        x -= state->speed;
        if (x < state->left)
            x = state->left;
    } else if (*keys & 0x10) {
        x += state->speed;
        if (x > state->right)
            x = state->right;
    }
    if (*keys & 0x40) {
        y -= state->speed;
        if (y < state->top)
            y = state->top;
    } else if (*keys & 0x80) {
        y += state->speed;
        if (y > state->bottom)
            y = state->bottom;
    }
    if ((s16)original_x != x || (s16)original_y != y)
        func_0801E5E0(x, y);
}
