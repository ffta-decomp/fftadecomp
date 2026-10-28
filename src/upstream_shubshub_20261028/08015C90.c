/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08015C90.c
 * Original SHA-256: 2f7f410a79e959b38f5fa6484ee1f3299946a44c7fb62b350c55a60d9d2c3e84
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *source;
    u8 unknown_04[0x0C];
    u8 x;
    u8 y;
    u8 unknown_12[2];
    u16 flags;
    u8 setting_a;
    u8 setting_b;
    u8 unknown_18[0x14];
} Window;

extern void func_08017528(void *output, void *source, const void *content,
                          u8 x, u8 y, u8 width, u8 height, u8 setting_a,
                          u16 first, u8 setting_b, u16 second);

/* Complete [0x08015C90, 0x08015D58): 200 bytes, 99 instructions. */
void func_08015C90(void *object, const void *content, u8 width,
                   u8 height, u16 first, u16 second)
{
    void *output = (u8 *)object + 0x2C;
    const Window *window = object;
    u8 x = window->x + 1;
    u8 y = window->y + 1;
    u8 inner_width = width - 2;
    u8 inner_height = (height - 2) / 2;

    if (window->flags & 2) {
        x = window->x;
        inner_width = width;
    }
    if (window->flags & 4) {
        u32 even_height;
        y = window->y;
        even_height = height;
        if (height & 1)
            even_height = height + 1;
        inner_height = (u8)even_height / 2;
    }
    if ((window->flags & 0xC20) == 0) {
        y++;
        inner_height = (u8)(height - 3) / 2;
    }
    func_08017528(output, window->source, content, x, y, inner_width,
                   inner_height, window->setting_a, first,
                   window->setting_b, second);
}
