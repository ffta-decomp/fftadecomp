/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812F008.c
 * Original SHA-256: cb8a22bb9eeac42e647d16c494474544baf347c3fbfab3a42572e220427e2514
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0812F008..0x0812F052: 74 bytes. */
typedef struct {
    u8 unknown_00[0xF6];
    s8 x;
    s8 y;
    s8 height;
} UnitPosition;

extern u32 func_0812D1DC(UnitPosition *first, UnitPosition *second,
                         s8 first_x, s8 first_y, s8 second_x, s8 second_y,
                         s8 height, u32 options);

u32 func_0812F008(UnitPosition *first, UnitPosition *second, u32 options)
{
    return func_0812D1DC(first, second, first->x, first->y,
                  second->x, second->y, second->height, options);
}
