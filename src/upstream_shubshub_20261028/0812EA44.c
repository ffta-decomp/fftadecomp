/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812EA44.c
 * Original SHA-256: 28ec2e00e143811e3e49488759c8fa8dd1ad7e588acbb582c7ee794cd2ce8cda
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0812EA44..0x0812EACA: 134 bytes, 63 reachable instructions. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 unknown_F8[5];
    u8 movement;
} Unit;

extern u16 func_0812E6A4(const Unit *);
extern u8 func_0801CC7C(u8, u8);
extern u32 func_0801CD08(u8, u8);
extern u8 func_0812E6E0(const Unit *, const Unit *, u16, u16);

static inline u8 valid_position(const Unit *unit)
{
    u32 x = unit->x;
    u32 y = unit->y;

    if (!func_0801CC7C(x, y) ||
        (unit->movement == 2 && (func_0801CD08(x, y) & 2)))
        return 0;
    else
        return 1;
}

u16 func_0812EA44(const Unit *source, const Unit *target, u16 identifier)
{
    u16 value = func_0812E6A4(target);

    if (value && valid_position(target) &&
        func_0812E6E0(source, target, identifier, value))
        return value;
    return 0;
}
