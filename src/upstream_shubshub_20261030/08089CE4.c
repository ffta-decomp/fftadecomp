/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08089CE4.c
 * Original SHA-256: 0f840b4041507c68c448a7422b28c3db43308d70ee40073a2c4f87c4069fd3fd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u32 first;
    u32 second;
} DisplayRecord;

typedef struct {
    u32 active : 1;
    u32 enabled : 1;
    u32 visible : 1;
    u32 palette : 4;
    u32 unknown_07 : 1;
    u32 mode : 2;
    u32 variant : 1;
    u32 style : 2;
    u32 pending : 1;
    u32 reserved : 4;
    u32 unknown_12 : 14;
    DisplayRecord entries[32];
    u8 count;
    u8 option;
    u8 selection;
    u8 unknown_107;
    u16 timer;
    u16 delay;
    u8 counter;
    u8 graphic;
    u8 state;
    u8 unknown_10f;
    u8 width;
    u8 height;
} DisplayObject;

typedef struct {
    u32 unknown_00;
    Entry *surface;
} RenderState;

extern RenderState data_03000E30;
extern const u8 data_08950D38[];
extern const u8 data_089514F4[];
extern void func_0804C4D4(Entry *base, u16 index, u16 selector,
                         u8 width, u8 count, u8 mode, u8 delay,
                         const u8 *graphics, const u8 *layout, u16 attributes);

/* 0x08089CE4..0x08089D64: 128 bytes, 52 instructions. */
void func_08089CE4(DisplayObject *object)
{
    object->pending = 1;
    object->active = 1;
    if (object->mode == 1) {
        func_0804C4D4(data_03000E30.surface, object->graphic,
                      object->variant + 2, object->width, object->height,
                      0, object->palette, data_08950D38, data_089514F4, 0x120);
    }
}
