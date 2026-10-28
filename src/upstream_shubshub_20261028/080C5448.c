/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C5448.c
 * Original SHA-256: 4da0f8bf579195cc8ff378e17bc552104992f4de7fa4374896cdbe800d5e7dbd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080C5448..0x080C55D8: 400 bytes, 174 instructions, including pools. */
typedef struct {
    u8 index;
    u8 flags;
    u8 mode;
    u8 unknown_03;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
} Marker;

typedef struct {
    u8 first;
    u8 second;
    u8 third;
    u8 unknown_03;
} MarkerColor;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} MarkerOffset;

extern const MarkerColor data_0839465C[];
extern const u8 data_0839469C[];
extern const MarkerOffset data_083946A0[];
extern const MarkerOffset data_083946C0[];
extern const MarkerOffset data_0839470C[];
extern const u8 data_0839474C[];
extern const u8 data_08394754[];
extern u8 func_080C72E4(void);
extern void func_08001F34(const void *image, s32 x, s32 y, u32 mode,
                         u32 a4, u32 a5, u32 a6, u32 a7, u32 a8,
                         u32 a9, u32 a10);

void func_080C5448(const Marker *marker)
{
    if (!(marker->flags & 2)) {
        return;
    }
    if (!(marker->flags & 1)) {
        return;
    }
    switch (marker->mode) {
    case 2: {
        u8 index = marker->index;
        func_08001F34(data_0839474C,
                     marker->x + marker->offset_x,
                     marker->y + marker->offset_y, 0, 0, 0,
                     data_0839465C[index].second,
                     data_0839465C[index].third,
                     data_0839465C[index].first, 0, 0);
        break;
    }
    case 3: {
        u8 index = marker->index;
        func_08001F34(data_0839474C,
                     marker->x + marker->offset_x,
                     marker->y + marker->offset_y, 0, 0, 0, 0, 0,
                     data_0839469C[index], 0, 0);
        break;
    }
    case 1: {
        u8 index = marker->index;
        u8 variant = func_080C72E4();
        if (variant) {
            func_08001F34(data_08394754,
                         marker->x + marker->offset_x + data_083946A0[index].x,
                         marker->y + marker->offset_y + data_083946A0[index].y,
                         0, 0, 0, 0, 0, 0, 0, 0);
        } else {
            func_08001F34(data_08394754,
                         marker->x + marker->offset_x + data_083946C0[index].x,
                         marker->y + marker->offset_y + data_083946C0[index].y,
                         0, 0, 0, 0, 0, 0, 0, 0);
        }
        break;
    }
    default: {
        u8 index = marker->index;
        func_08001F34(data_08394754,
                     marker->x + marker->offset_x + data_0839470C[index].x,
                     marker->y + marker->offset_y + data_0839470C[index].y,
                     0, 0, 0, 0, 0, 0, 0, 0);
        break;
    }
    }
}
