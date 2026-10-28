/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809995C.c
 * Original SHA-256: ca59deaed96afcb3d9c643a9d761f7a355e0743acce50d3952b6fea6017649b6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xfd];
    u8 movement;
} Unit0809995C;

typedef struct {
    Unit0809995C *unit;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 y;
} Context0809995C;

typedef struct {
    s32 x : 16;
    s32 height : 16;
    s32 y : 16;
} Position0809995C;

extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);

/* Complete [0x0809995C, 0x08099A0C): 176 bytes, 80 instructions. */
u8 func_0809995C(Context0809995C *context)
{
    Position0809995C position;

    position.height = context->height >> 4;
    position.x = context->x >> 5;
    position.y = context->y >> 5;
    if (context->unit->movement != 2)
        return 0;
    if (position.x < 0 || position.y < 0 || position.x > 15 || position.y > 15)
        return 0;
    if (!func_0801CC7C((u16)position.x, (u16)position.y))
        return 0;
    if (!(func_0801CD08((u16)position.x, (u16)position.y) & 2))
        return 0;
    if ((s8)func_0801CC18((u16)position.x, (u16)position.y) <= position.height)
        return 0;
    return 1;
}
