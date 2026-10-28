/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08012950.c
 * Original SHA-256: a135a0c9d14cd884a5fa8366d8a396b1e231d63e87e3a2b753df3cf40c0784e2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 status;
    u8 unknown_09[2];
    u8 variant;
    u16 flags;
    u8 unknown_0e[8];
    u16 scale;
    u16 limit;
    u8 unknown_1a[0x0d];
    u8 handle;
    u8 sound_played;
    u8 unknown_29[2];
    u8 extra;
    u8 unknown_2c[0x0e];
    u16 options;
    u8 unknown_3c[8];
    u8 object[0x2c];
    u8 renderer[0x290];
    u8 *buffer;
    u8 *selected;
    const u8 *active;
} Context08012950;

typedef struct {
    u8 unknown_0000[0x2fc0];
    u8 sound_flags;
} Global08012950;

extern Context08012950 *data_0200918C;
extern Global08012950 g_state_02000000;
extern u8 func_08012910(void);
extern void func_08017508(void *, u8);
extern void func_08011EA4(void);
extern u8 func_080098F4(void (*)(void), u8);
extern void func_0801360C(void *, u16);
extern void func_08141540(u16);
extern u8 func_080120F0(void);

/* 0x08012950..0x08012A98: 328 bytes, 139 instructions. */
u8 func_08012950(u8 immediate)
{
    s32 forced = 0;

    if (immediate) {
        data_0200918C->limit = 0x8000;
        forced = 1;
    } else {
        if (data_0200918C->limit + data_0200918C->scale <= 0x7fff)
            data_0200918C->limit += data_0200918C->scale;
    }

    while (data_0200918C->limit > 0x100) {
        u8 code = *data_0200918C->active;

        if (code == 0) {
            if (!func_08012910()) {
                func_08017508(data_0200918C->object, data_0200918C->variant);
                if (data_0200918C->extra)
                    data_0200918C->options &= 0xfeff;
                if (!(data_0200918C->flags & 0x1000))
                    data_0200918C->handle = func_080098F4(func_08011EA4, 0);
                data_0200918C->status = 3;
                break;
            }
        } else if (code & 0x80) {
            func_0801360C(data_0200918C->renderer,
                          ((code << 8) | data_0200918C->active[1]) & 0x7fff);
            data_0200918C->active += 2;
            if (!data_0200918C->sound_played && !forced) {
                func_08141540(0x6e);
                if ((g_state_02000000.sound_flags & 0x18) == 8)
                    data_0200918C->sound_played = 1;
            }
        } else if (code == 0x40) {
            if (func_080120F0())
                break;
        }
        data_0200918C->limit -= 0x100;
    }
    return data_0200918C->status;
}
