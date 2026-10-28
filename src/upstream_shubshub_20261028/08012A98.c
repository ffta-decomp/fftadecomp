/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08012A98.c
 * Original SHA-256: faaf0cf48a686ff38b92b0c51c1d808bbe3824c0d12b4e691382b1406ec1d5f5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    const void *data;
} Resource08012A98;

typedef struct {
    Resource08012A98 *resource;
    u8 unknown_04[6];
    u8 mode;
    u8 unknown_0b;
    u16 flags;
    u8 column;
    u8 row;
    u8 unknown_10;
    u8 height;
    u16 parameter;
    u8 unknown_14[6];
    u8 stride;
    u8 unknown_1b[0x10];
    u8 column_flags;
    u8 unknown_2c[0x44];
    u8 drawing[0x290];
    u8 *buffer;
    const void *input;
} Context08012A98;

extern Context08012A98 *data_0200918C;

extern u8 func_0801843C(u8 mode);
extern u8 func_08018484(u8 mode);
extern u8 func_08018470(u8 mode);
extern void func_08013570(void *drawing, const void *input, u8 stride, u32 mode);
extern void func_08013528(void *drawing, const void *input);
extern void func_080137C0(void *drawing, u32 value);
extern void func_08013A88(void *buffer, u32 length);
extern void func_080157A8(const void *source, u8 column, u8 row, u8 stride,
                          u32 rows, u32 width, u16 parameter, u32 mode);
extern void func_08015858(const void *source, u8 column, u8 row, u8 stride,
                          u32 rows, u32 width, u16 parameter, u32 mode);

/* 0x08012A98 - 338 bytes, including literal pools. */
void func_08012A98(void)
{
    u8 column;
    s32 i;
    u32 mode;
    u8 row_offset;

    if (func_0801843C(data_0200918C->mode)) {
        func_08013570(data_0200918C->drawing, data_0200918C->input,
                      data_0200918C->stride, 1);
    } else {
        func_08013528(data_0200918C->drawing, data_0200918C->input);
    }
    if (func_08018484(data_0200918C->mode))
        func_080137C0(data_0200918C->drawing, 5);

    if (data_0200918C->column_flags != 0 || (data_0200918C->flags & 0x10)) {
        if (data_0200918C->column_flags & 1)
            column = data_0200918C->column + 8;
        else
            column = data_0200918C->column + 3;
    } else {
        column = data_0200918C->column + 1;
    }

    for (i = 0; i < data_0200918C->height / 2; i++) {
        func_08013A88(data_0200918C->buffer + i * data_0200918C->stride * 64,
                      data_0200918C->stride * 2);
    }

    mode = func_08018484(data_0200918C->mode) ? 11 : 12;
    row_offset = (data_0200918C->flags & 0xc0) ? 2 : 1;

    if (!func_08018470(data_0200918C->mode)) {
        Context08012A98 *context = data_0200918C;

        func_080157A8(context->resource->data, column,
                      (u8)(row_offset + context->row), context->stride,
                      context->height / 2, 32, context->parameter, mode);
    } else {
        Context08012A98 *context = data_0200918C;

        func_08015858(context->resource->data, column,
                      (u8)(row_offset + context->row), context->stride,
                      context->height / 2, 32, context->parameter, mode);
    }
}
