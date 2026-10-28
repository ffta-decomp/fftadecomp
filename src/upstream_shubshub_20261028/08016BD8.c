/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08016BD8.c
 * Original SHA-256: b2c260832863d551f70e8501f207d0c75903dc585c2e4dab900f96560bb97184
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Rectangle {
    u8 left;
    u8 top;
    u8 width;
    u8 height;
} Rectangle;

typedef struct Window {
    const u16 *first_source;
    const u16 *second_source;
    u16 *first_buffer;
    u16 *second_buffer;
    u8 left;
    u8 top;
    u8 width;
    u8 height;
    u8 unknown_14[2];
    u8 palette;
    u8 unknown_17[5];
    u8 flags;
} Window;

extern void func_08016AEC(u16 *destination, u32 stride,
                          const u16 *source, Rectangle area, u8 palette);

static inline void set_rectangle(Rectangle *area, u8 left, u8 top,
                                  u8 width, u8 height)
{
    area->left = left;
    area->top = top;
    area->width = width;
    area->height = height;
}

/* 08016BD8..08016C90: 184 bytes, 88 instructions. */
void func_08016BD8(Window *window, u16 *buffer)
{
    Rectangle area;

    if (window->flags & 8) {
        set_rectangle(&area, 0, window->top - 1, 30, window->height + 2);

        window->first_buffer = buffer;
        func_08016AEC(buffer, 30, window->first_source, area, window->palette);
        if (window->second_source != 0) {
            window->second_buffer = window->first_buffer + (window->height + 2) * 30;
            func_08016AEC(window->second_buffer, 30, window->second_source,
                          area, window->palette);
        }
    } else {
        set_rectangle(&area, window->left, window->top,
                       window->width, window->height);

        window->first_buffer = buffer;
        func_08016AEC(buffer, window->width, window->first_source, area,
                      window->palette);
        if (window->second_source != 0) {
            window->second_buffer = window->first_buffer + window->width * window->height;
            func_08016AEC(window->second_buffer, window->width, window->second_source,
                          area, window->palette);
        }
    }
}
