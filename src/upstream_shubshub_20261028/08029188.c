/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08029188.c
 * Original SHA-256: f54c18a283e2d716849c15fab50fe6e285a446d26899574f224c961f080e06c9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 mode;
    u8 unknown_02[0x12];
    u16 selection;
} MenuEvent;

typedef struct {
    u8 unknown_00[0x28];
} TileRegion;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
} WindowBounds;

typedef struct {
    void *owner;
    u32 timer;
    u8 selection;
    u8 unknown_09[3];
    TileRegion region;
    u8 unknown_34[0x4C];
    WindowBounds bounds;
} MenuWork;

typedef struct {
    u8 unknown_00[0x0E];
    u16 pending;
} MenuControl;

typedef void (*CopyCallback)(void *destination, const void *source, u32 size);

extern const CopyCallback data_0836D4BC[];
extern u8 data_030039C8[];
extern MenuControl *data_0200F438;

void func_08027DA0(MenuWork *work);
void func_080282D4(MenuWork *work);
void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
u8 *func_080CBA84(u32 index);
void func_0802800C(MenuWork *work);
u8 func_080172F0(TileRegion *region);
void func_08025DC8(MenuWork *work, u32 update);
void func_08017508(TileRegion *region, u8 appearance);

/* Complete [0x08029188, 0x080292A0): 280 bytes. */
u32 func_08029188(void *owner, MenuEvent *event, MenuWork *work)
{
    switch (event->mode) {
    case 0:
        work->owner = owner;
        work->timer = 0;
        work->selection = event->selection;
        break;
    case 1:
        break;
    case 0x100:
        {
            WindowBounds *bounds = &work->bounds;

            func_08027DA0(work);
            func_080282D4(work);
            func_0802A2C0(bounds->x, bounds->y, bounds->width, bounds->height);
            event->mode = 0x101;
        }
        break;
    case 0x104:
        {
            const CopyCallback *callbacks;
            u8 *destination;

            func_0802A2C0(0, 0, 0, 0);
            callbacks = data_0836D4BC;
            destination = data_030039C8;
            callbacks[0](destination, func_080CBA84(11) + 8, 6);
            destination += 0x12;
            callbacks[0](destination, func_080CBA84(11) + 0x1A, 6);
            func_0802800C(work);
            event->mode = 3;
        }
        break;
    case 0x101:
        if (func_080172F0(&work->region)) {
            func_08025DC8(work, 1);
            event->mode = 0x102;
        }
        break;
    case 0x103:
        if (func_080172F0(&work->region))
            event->mode = 0x104;
        break;
    case 0x102:
        if (data_0200F438->pending == 0) {
            func_08017508(&work->region, 0x10);
            event->mode = 0x103;
        }
        break;
    }
    return 0;
}
