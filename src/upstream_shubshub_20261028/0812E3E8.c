/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812E3E8.c
 * Original SHA-256: 0770ed4232281d30c24465e475c8e16f3ef85666610dc5850d15aeeb8758a2aa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct
{
    u8 unknown_00[0xFC];
    u8 movement;
    u8 terrain_movement;
} Unit;

extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);

/* Complete target: 0x0812E3E8..0x0812E46E, 134 bytes. */
u32 func_0812E3E8(const Unit *unit, s8 column, s8 row)
{
    u8 flags;

    if (column < 0 || row < 0 || column > 15 || row > 15)
        return 0;
    if (!func_0801CC7C(column, row))
        return 0;

    flags = func_0801CD08(column, row);
    if (flags & 1)
        return 0;
    if (flags & 8)
        return 0;
    if (flags & 2)
    {
        if ((u8)(unit->terrain_movement - 2) <= 2)
            return 1;
        return 0;
    }
    if (!(flags & 4))
        return 1;
    if (unit->movement == 4)
        return 1;
    return 0;
}
