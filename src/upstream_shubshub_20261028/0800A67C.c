/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800A67C.c
 * Original SHA-256: 876c20ff7dc942bbfaffbb08cbb958f211c63d17894320bebe930499626357c2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800A67C..0x0800A71C: 160 bytes. */

typedef struct {
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
} TileBounds;

typedef struct {
    u8 record;
    u8 unknown_01[0x1B];
    TileBounds bounds;
} View;

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[6];
    u16 x;
    u16 y;
    u8 unknown_1C[2];
    s16 targetX;
    s16 targetY;
    u8 unknown_22[6];
} ViewRecord;

extern ViewRecord g_records_02009000[];

static inline s32 coordinate_difference(u16 origin, s16 position)
{
    return position - origin;
}

void func_0800A67C(View *view, TileBounds *bounds)
{
    ViewRecord *record;
    s16 x;
    s16 y;

    bounds->left = view->bounds.left;
    bounds->top = view->bounds.top;
    bounds->right = view->bounds.right;
    bounds->bottom = view->bounds.bottom;
    record = &g_records_02009000[view->record];
    if (record->flags & 0x20) {
        x = coordinate_difference(record->x, record->targetX);
        y = coordinate_difference(record->y, record->targetY);
        if (x < 8) {
            bounds->left = 0;
            bounds->right = (x + 247) >> 3;
        } else {
            bounds->left = x >> 3;
            bounds->right = (x >> 3) + (((x & 0xFFF8) + 247) >> 3);
        }
        if (y < 8) {
            bounds->top = 0;
            bounds->bottom = (y + 167) >> 3;
        } else {
            bounds->top = y >> 3;
            bounds->bottom = (y >> 3) + (((y & 0xFFF8) + 167) >> 3);
        }
    }
}
