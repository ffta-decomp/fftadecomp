/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08081078.c
 * Original SHA-256: 03301c13b280dc5e184a1b2dc0cc0a28a93a18e3044fa4f8d54b8c0401e703f1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 x_offset;
    u16 y_offset;
} DrawRect;

typedef struct {
    u8 unknown_00;
    u8 layer;
    u8 unknown_02[0x32];
    s8 x;
    s8 y;
    u8 unknown_36[0x12];
    s8 x_offset;
    s8 y_offset;
    u8 unknown_4A[2];
} RenderObject;

typedef struct {
    u8 unknown_000[0x95E];
    u8 flags;
} Context;

extern Context *data_03002818;
extern RenderObject data_030009E0[];
extern const u8 data_08393C6A[];
extern const u8 data_0851BA52[];
extern void func_08001F34(const void *graphic, s32 x, s32 y, u32 a4,
                          u32 a5, u32 a6, u32 a7, u32 a8, u32 a9,
                          u32 layer, u32 a11);

/* Complete target: [0x08081078, 0x0808118C), 276 bytes, 123 instructions. */
void func_08081078(u32 index, void *geometry)
{
    DrawRect *rect = geometry;

    if ((data_03002818->flags & 0x0C) == 8) {
        func_08001F34(data_08393C6A,
            rect->x + rect->x_offset +
                (data_030009E0[index].x + data_030009E0[index].x_offset - 1) * 8,
            rect->y + rect->y_offset +
                (data_030009E0[index].y + data_030009E0[index].y_offset - 1) * 8,
            0, 0, 0, 0, 0, 0, data_030009E0[index].layer, 0);
    } else if (index != 7) {
        func_08001F34(data_0851BA52,
            rect->x + rect->x_offset +
                (data_030009E0[index].x + data_030009E0[index].x_offset - 1) * 8,
            rect->y + rect->y_offset +
                (data_030009E0[index].y + data_030009E0[index].y_offset - 1) * 8,
            0, 0, 0, 0, 0, 0, data_030009E0[index].layer, 0);
    }
}
