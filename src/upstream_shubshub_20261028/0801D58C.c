/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801D58C.c
 * Original SHA-256: eaceeb98cab6e8eb95f0b680e7407da4767d2a0618e3d6538b89675bd3f871e2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801D58C .. 0x0801D624: 152 bytes. */
typedef struct {
    u8 active;
    u8 mode;
    u8 unknown_02[38];
    u8 first[16][16];
    u8 second[16][16];
} Grid0801D58C;

extern Grid0801D58C data_02008168;

static inline u8 grid_active(const Grid0801D58C *grid)
{
    if (!grid->active || grid->mode != 3)
        return 0;
    return 1;
}

u32 func_0801D58C(u8 x, u8 y)
{
    const Grid0801D58C *grid = &data_02008168;
    u8 first;
    u8 second;
    u32 result;

    if (!grid_active(grid))
        return 0;

    first = grid->first[y][x];
    second = grid->second[y][x];
    result = 0;
    if (first) {
        u32 pair;

        if ((pair = first >> 6) != 0)
            result = pair;
        else if ((pair = (first >> 4) & 3) != 0)
            result = pair;
        else if ((pair = (first >> 2) & 3) != 0)
            result = pair;
        else if ((pair = first & 3) != 0)
            result = pair;
    } else if (second) {
        u32 pair;

        if ((pair = second >> 6) != 0)
            result = pair;
        else if ((pair = (second >> 4) & 3) != 0)
            result = pair;
        else if ((pair = (second >> 2) & 3) != 0)
            result = pair;
        else if ((pair = second & 3) != 0)
            result = pair;
    }
    return result;
}
