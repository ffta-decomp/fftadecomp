/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08066EA0.c
 * Original SHA-256: 759c01637e898ea874d39860d8b4cdd738c606a2933ab9ab5791411ea392a196
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
    u8 unknown_13[0x0D];
    u16 draw_width;
    u16 draw_height;
} Window;

typedef struct {
    u8 unknown_00[0x28];
    Window window;
} Menu;

extern u8 func_08017180(Window *window);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);

/* Complete target: [0x08066EA0, 0x08066ED8), 56 bytes, 26 instructions. */
u8 func_08066EA0(Menu *menu)
{
    Window *window = &menu->window;
    u8 result = func_08017180(window);

    func_0802A2C0(window->width - window->draw_width + window->x, window->y,
                  window->draw_width, window->draw_height);
    return result;
}
