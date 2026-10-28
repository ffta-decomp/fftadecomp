/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080366BC.c
 * Original SHA-256: 18f158b8ed7f245f0d8ab211c95408ba5c341f89c08d461329b4fbe593346e79
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 flags;
    u8 unknown_04[2];
    s16 anchor_x;
    u16 anchor_y;
    u8 unknown_0a[2];
    u16 scroll_y;
    u8 unknown_0e[4];
    u8 mode;
    u8 dirty_x : 1;
    u8 dirty_y : 1;
    u8 unknown_13 : 6;
    s16 x;
    s16 y;
    u8 unknown_18[0x8c - 0x18];
    u8 selection;
} MenuWindow;

typedef struct {
    void *owner;
    MenuWindow *window;
    u8 background[0x674 - 8];
    u8 cached_selection;
    u8 unknown_675[3];
    const void *graphic;
    u8 unknown_67c[0xf3e - 0x67c];
    u8 delay;
} MenuContext;

extern MenuContext *g_state_03002810;
extern const u8 data_08391DE4[];
extern const void *data_08391A48[];
extern const u8 data_083AB42C[];
extern const u16 data_08391E02[];
extern u8 data_02003CB0[];
extern u16 data_06010980[];
extern void func_08005318(const void *source, void *destination, u32 length, u32 width);
extern void func_08000A98(void *background, const void *source, void *destination, u16 attributes);
extern void func_08001F34(const void *graphic, s32 x, s32 y, u32 a3,
                         u32 a4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10);

/* Complete target: [0x080366BC, 0x0803687A), 446 bytes. */
void func_080366BC(void)
{
    MenuContext *context = g_state_03002810;
    u8 index = (context->window->selection - 1) & 0x7f;
    s32 width;
    s32 x;
    s32 y;

    if (context->delay) {
        context->delay--;
        return;
    }
    width = data_08391DE4[index];
    if (context->cached_selection != index + 1) {
        u8 *buffer = data_02003CB0;
        context->cached_selection = index + 1;
        g_state_03002810->graphic = data_08391A48[width];
        func_08005318(data_083AB42C, buffer,
                      data_08391E02[index] >> 1, width + 5);
        func_08000A98(g_state_03002810->background, buffer,
                      data_06010980, (u16)(0xa0 + (width << 5)));
    }
    width += 5;
    x = g_state_03002810->window->anchor_x - width * 4;
    if (x < 0)
        x = 0;
    else if (x + width * 8 > 240)
        x = 240 - width * 8;

    g_state_03002810->window->x = x;
    g_state_03002810->window->y = g_state_03002810->window->anchor_y + 10;
    g_state_03002810->window->dirty_x = 1;
    g_state_03002810->window->dirty_y = 1;
    y = g_state_03002810->window->y - g_state_03002810->window->scroll_y;
    if (y > 144)
        y = 144;

    switch (g_state_03002810->window->mode) {
    case 0:
        func_08001F34(g_state_03002810->graphic, x, y, 0, 0, 0, 0, 0, 0, 2, 0);
        break;
    case 1:
        if ((g_state_03002810->window->flags & 0xf) > 2)
            func_08001F34(g_state_03002810->graphic, x, y, 0, 0, 0, 0, 0, 0, 2, 0);
        else
            func_08001F34(g_state_03002810->graphic, x, 240, 0, 0, 0, 0, 0, 0, 2, 0);
        break;
    case 2:
        if ((g_state_03002810->window->flags & 7) > 1)
            func_08001F34(g_state_03002810->graphic, x, y, 0, 0, 0, 0, 0, 0, 2, 0);
        else
            func_08001F34(g_state_03002810->graphic, x, 240, 0, 0, 0, 0, 0, 0, 2, 0);
        break;
    }
}
