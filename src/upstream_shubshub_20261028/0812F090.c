/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812F090.c
 * Original SHA-256: 56391514819b1e4aebee16109fde9f5a68e66cb1b0a69a0b20e065e8837cf855
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0812F090..0x0812F0CA: 58 bytes. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit;

extern s32 func_0812E1A8(void *, u8, u8, u8, u8, u16, u8);

s32 func_0812F090(Unit *unit, u8 to_x, u8 to_y, u16 item, u8 flags)
{
    return func_0812E1A8(unit, unit->x, unit->y, to_x, to_y, item, flags);
}
