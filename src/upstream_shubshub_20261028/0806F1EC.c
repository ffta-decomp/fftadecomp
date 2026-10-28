/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806F1EC.c
 * Original SHA-256: aa2ac76426dff6233259634b8b13632a64ca114c2e63c9055f77773a43bd1981
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s8 x;
    s8 y;
} Position0806F1EC;

struct Tilemap0806F1EC;
extern struct Tilemap0806F1EC data_030008B0;
extern struct Tilemap0806F1EC data_03000990;
extern void func_0802B2E8(struct Tilemap0806F1EC *, u8 x, u8 y,
                          u8 width, u8 height);
extern void func_0806F050(Position0806F1EC *, s32 x, s32 y);

/* 0x0806F1EC..0x0806F2E0: 244 bytes, 107 instructions. */
u32 func_0806F1EC(Position0806F1EC *position, s8 target)
{
    s8 difference;
    s8 previous;
    s8 start;

    if (position->x == (s8)target)
        return 1;
    difference = target - position->x;
    previous = position->x;
    if (difference > 0) {
        position->x += 4;
        if (position->x >= (s8)target)
            position->x = target;
        if (position->x > 0) {
            start = previous < 0 ? 0 : previous;
            func_0802B2E8(&data_030008B0, start, position->y,
                          position->x - start, 8);
            func_0802B2E8(&data_03000990, start, position->y,
                          position->x - start, 8);
        }
    } else {
        s32 left;
        position->x -= 4;
        if (position->x < (s8)target)
            position->x = target;
        start = position->x + 14 < 0 ? 0 : position->x + 14;
        left = start - 14;
        previous -= left;
        if (previous > 0) {
            func_0802B2E8(&data_030008B0, start, position->y, previous, 8);
            func_0802B2E8(&data_03000990, start, position->y, previous, 8);
        }
    }
    func_0806F050(position, position->x, position->y);
    return 0;
}
