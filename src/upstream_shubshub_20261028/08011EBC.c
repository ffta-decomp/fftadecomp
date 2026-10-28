/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011EBC.c
 * Original SHA-256: e9b8f2eebadb5a2577a5f440932c4f37929cedc37e4d6a3865e0b2d71d4976a1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Resource08011EBC {
    u8 unknown_00[0x14];
    u32 value;
};

struct Object08011EBC {
    u8 unknown_00[0x1c];
    u8 flags;
    u8 unknown_1d[0x74c - 0x1d];
};

struct Context08011EBC {
    struct Resource08011EBC *first;
    struct Resource08011EBC *second;
    u8 unknown_08[2];
    u8 kind;
    u8 variant;
    u16 flags;
    u8 left;
    u8 top;
    u8 width;
    u8 height;
    u8 unknown_12[0x0b];
    u8 value_1d;
    u8 value_1e;
    u8 value_1f;
    u8 unknown_20[7];
    u8 handle;
    u8 unknown_28[3];
    u8 extra;
    u8 unknown_2c[0x0e];
    u16 options;
    u8 unknown_3c[8];
    struct Object08011EBC object;
    u8 alternate_data[0];
};

extern struct Context08011EBC *data_0200918C;
extern u8 data_02004EB0[];
extern void func_08017424(struct Object08011EBC *, u32, u32,
                          u8, u8, u8, u8, u16, u8, u16, u16, u8);
extern void func_08016BD8(struct Object08011EBC *, void *);
extern u8 func_080184D0(u8);
extern void func_08016E1C(struct Object08011EBC *, u8, u8);
extern void func_08016E4C(struct Object08011EBC *, const void *, u8);
extern void func_08141540(u16);
extern void func_08016C90(struct Object08011EBC *, u8);
extern void func_08012014(void);
extern void func_08011EA4(void);
extern u8 func_080098F4(void (*)(void), u8);

/* Target: [0x08011EBC, 0x08012014), 344 bytes, 154 instructions. */
void func_08011EBC(void)
{
    struct Context08011EBC *context = data_0200918C;
    struct Object08011EBC *object = &context->object;
    u8 horizontal_margin = (context->flags & 0x20) ? 3 : 2;
    u8 vertical_margin = (context->flags & 0xc0) ? 3 : 2;

    func_08017424(object, context->first->value, context->second->value,
                   context->left, context->top,
                   (u8)(horizontal_margin + context->width),
                   (u8)(vertical_margin + context->height),
                   context->flags, 0x20, context->value_1d,
                   context->value_1e, context->value_1f);
    if (data_0200918C->options & 2) {
        if (data_0200918C->options & 0x200)
            object->flags |= 8;
        func_08016BD8(object, data_0200918C->alternate_data);
    }
    if ((data_0200918C->flags & 0x20) || func_080184D0(data_0200918C->kind))
        object->flags |= 1;
    if (data_0200918C->options & 0x3c) {
        u8 mode = 1;

        if (data_0200918C->options & 0x20)
            mode = 0x18;
        else if (data_0200918C->options & 0x10)
            mode = 0x1b;
        else if (data_0200918C->options & 4)
            mode = 2;
        func_08016E1C(object, mode, 0);
        func_08016E4C(object, data_02004EB0, 1);
    }
    if (func_080184D0(data_0200918C->kind))
        func_08141540(0x70);
    func_08016C90(object, data_0200918C->variant);
    if (data_0200918C->extra != 0)
        func_08012014();
    data_0200918C->handle = func_080098F4(func_08011EA4, 0);
}
