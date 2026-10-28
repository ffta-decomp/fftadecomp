/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BD35C.c
 * Original SHA-256: ffa545a34500ce003691f7c0b58f53c248450826826b1886c12cae6c74fa32be
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *unit;
} MapEntry;

extern MapEntry *func_08099644(void *world, s8 x, s8 y);
extern u8 func_080CD92C(void *unit);
extern u8 func_080C8280(void *unit);

static inline u8 occupied_ray(void *world, s8 x, s8 y, s8 step_x,
                              s8 step_y, s8 length)
{
    s8 i;

    for (i = 0; i < length; i++, x += step_x, y += step_y) {
        MapEntry *entry;

        if (x < 0 || y < 0 || x > 15 || y > 15)
            return 0;
        entry = func_08099644(world, x, y);
        if (entry == 0)
            return 0;
        if (!func_080CD92C(entry->unit) && !func_080C8280(entry->unit))
            return 0;
    }
    return 1;
}

/* 0x080BD35C..0x080BD7D2: 1142 bytes. */
u8 func_080BD35C(void *world, s8 x, s8 y, s8 length)
{
    s8 half = length >> 1;

    if (occupied_ray(world, x - half, y, 1, 0, length))
        return 1;
    if (occupied_ray(world, x, y, 1, 0, length))
        return 1;
    if (occupied_ray(world, x, y - half, 0, 1, length))
        return 1;
    if (occupied_ray(world, x, y, 0, 1, length))
        return 1;
    if (occupied_ray(world, x - half, y - half, 1, 1, length))
        return 1;
    if (occupied_ray(world, x, y, 1, 1, length))
        return 1;
    if (occupied_ray(world, x + half, y - half, -1, 1, length))
        return 1;
    if (occupied_ray(world, x, y, -1, 1, length))
        return 1;
    return 0;
}
