/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8384.c
 * Original SHA-256: fa5ba8a8431805963524f04c148be51045ba8ed49f1a17c38e7f435e1cfeff86
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D8384..0x080D850E: 394 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *first_destination;
    void *second_destination;
    u8 unknown_0C[8];
    u16 mode;
    u16 palette;
} TilemapEvent;

typedef struct {
    u8 mode;
    u8 first;
    u8 second;
    u8 palette;
    s16 x;
    s16 y;
    s16 aligned_x;
    s16 aligned_y;
    u16 tiles[32][32];
    void *first_destination;
    void *second_destination;
} TilemapWork;

extern void func_0801E6F0(s16 *x, s16 *y);
extern void func_0801E0DC(s16 x, s16 y);
extern void func_0801E610(u8 *first, u8 *second);
extern void func_0801B630(int x, int y, int layer,
                          u16 *first, u16 *second);
extern int func_080D3AF8(void);
extern void func_08000A98(int channel, const void *source,
                          void *destination, u32 count);

static inline void apply_palette(TilemapWork *work)
{
    u8 row;
    u8 column;

    for (row = 0; row < 32; row++) {
        for (column = 0; column < 32; column++) {
            work->tiles[row][column] &= 0x0FFF;
            work->tiles[row][column] |= work->palette << 12;
        }
    }
}

int func_080D8384(void *unused, TilemapEvent *event, TilemapWork *work)
{
    switch (event->state) {
    case 0:
        work->mode = event->mode;
        work->palette = event->palette;
        work->first_destination = event->first_destination;
        work->second_destination = event->second_destination;
        func_0801E6F0(&work->x, &work->y);
        func_0801E0DC(work->x, work->y);
        func_0801E610(&work->first, &work->second);
        work->aligned_x = (work->x & ~7) - 8;
        work->aligned_y = (work->y & ~7) - 0x30;
        break;
    case 0x100:
        func_0801B630(work->aligned_x >> 3, work->aligned_y >> 3,
                       0, &work->tiles[0][0], 0);
        if (work->mode == 1)
            apply_palette(work);
        func_08000A98(func_080D3AF8(), work->tiles,
                       work->first_destination, 0x400);
        event->state++;
        break;
    case 0x101:
        func_0801B630(work->aligned_x >> 3, work->aligned_y >> 3,
                       0, 0, &work->tiles[0][0]);
        if (work->mode == 1)
            apply_palette(work);
        func_08000A98(func_080D3AF8(), work->tiles,
                       work->second_destination, 0x400);
        event->state++;
        break;
    case 0x102:
        event->state = 2;
        break;
    }
    return 0;
}
