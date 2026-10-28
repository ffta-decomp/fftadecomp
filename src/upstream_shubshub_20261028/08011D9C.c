/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011D9C.c
 * Original SHA-256: 0059286e63f19a8d9fef7b62074bc6c89ed94652a85161425e751e794818d79e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Layout08011D9C {
    u8 unknown_00[0x0c];
    u16 flags;
    s8 column;
    s8 row;
    u8 width;
    u8 height;
    u8 unknown_12[8];
    u8 base_width;
    u8 unknown_1b[0x10];
    u8 column_flags;
    u8 unknown_2c[0x0e];
    u16 options;
    u16 window_x;
    u16 window_y;
};

extern struct Layout08011D9C *data_0200918C;
extern void func_08012D3C(void);
extern u8 func_08013AAC(u8 width, u16 flags);
extern u8 func_08013ACC(u8 height, u16 flags);

/* Target: [0x08011D9C, 0x08011EA4), 264 bytes, 119 instructions. */
void func_08011D9C(void)
{
    u8 width;
    u8 height;

    func_08012D3C();
    data_0200918C->width = data_0200918C->base_width;
    if (data_0200918C->flags & 0x10)
        data_0200918C->width += 2;
    if (data_0200918C->column_flags) {
        data_0200918C->width += (data_0200918C->flags & 0x10) ? 6 : 8;
        if (data_0200918C->width > 27)
            data_0200918C->width = 27;
    }
    width = func_08013AAC(data_0200918C->width, data_0200918C->flags);
    height = func_08013ACC(data_0200918C->height >> 1, data_0200918C->flags);
    switch (data_0200918C->column) {
    case -1:
        data_0200918C->column = (30 - width) >> 1;
        break;
    case -2:
        data_0200918C->column = 30 - width;
        break;
    }
    switch (data_0200918C->row) {
    case -1:
        data_0200918C->row = (20 - height) >> 1;
        break;
    case -2:
        data_0200918C->row = 20 - height;
        break;
    }
    if (data_0200918C->column_flags) {
        if (data_0200918C->column_flags & 1)
            data_0200918C->window_x = 0;
        else
            data_0200918C->window_x = 0xf0;
        data_0200918C->window_y = (data_0200918C->row << 3) + 0x38;
    }
    data_0200918C->options &= 0xfeff;
}
