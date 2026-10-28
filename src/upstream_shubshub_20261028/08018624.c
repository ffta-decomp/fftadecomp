/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018624.c
 * Original SHA-256: f011216492c754da490be28cdc5e04f7b121c6017de46d56c822e18f787aec11
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08018624..0x08018790: 364 bytes, 166 instructions. */
typedef struct {
    u8 unknown_00[8];
    u8 active;
    u8 width;
    u8 x;
    u8 y;
    u16 tile;
    u8 flags;
    u8 unknown_0F;
    u8 height;
    u8 unknown_11[0x2BF];
    const u8 *source;
    u8 *graphics;
    u8 text[0x80];
    u8 workspace[0x80];
} PanelContext;

typedef struct {
    u8 unknown_00[8];
    const void *argument;
    u16 value;
} TextArguments;

typedef void (*BufferCopier)(void *, const void *, u32);
extern BufferCopier data_0836D4BC[];
extern PanelContext *data_02009190;
extern TextArguments g_state_020020D0;
extern u16 func_08014778(const u8 *text);
extern u16 func_080144F4(const u8 *text, u8 mode);
extern u16 func_08013E9C(u8 *destination, const u8 *source, u8 *workspace,
                         u16 index, u32 mode, u8 *height);
extern void func_08013A88(void *graphics, u16 count);
extern void func_08015110(void *context, void *graphics, const u8 *text,
                          u32 style, u32 spacing);

void func_08018624(u8 x, u8 y, u16 text, u8 width,
                   u16 value, const void *argument)
{
    g_state_020020D0.value = value;
    g_state_020020D0.argument = argument;
    data_02009190->flags = 0;
    if (text == 0xFFFF) {
        data_02009190->height = 1;
        data_0836D4BC[0](data_02009190->text, data_02009190->source, 0x80);
        if (width == 0)
            width = func_08014778(data_02009190->text) >> 3;
    } else {
        data_02009190->flags |= 2;
        func_08013E9C(data_02009190->text, data_02009190->source,
                      data_02009190->workspace, text, 0,
                      &data_02009190->height);
        if (width == 0)
            width = func_080144F4(data_02009190->text, 1) >> 3;
    }
    if (width & 1)
        width++;
    switch ((s8)x) {
    case -1:
        x = (28 - width) >> 1;
        break;
    case -2:
        x = 28 - width;
        break;
    }
    switch ((s8)y) {
    case -1:
        y = 9;
        break;
    case -2:
        y = 18;
        break;
    }
    data_02009190->x = x;
    data_02009190->y = y;
    data_02009190->width = width;
    func_08013A88(data_02009190->graphics,
                  width * data_02009190->height * 2);
    if (!(data_02009190->flags & 2))
        func_08015110((u8 *)data_02009190 + 0x40,
                      data_02009190->graphics, data_02009190->text, 5, 1);
    data_02009190->active = 1;
}
