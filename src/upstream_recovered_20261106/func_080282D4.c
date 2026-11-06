/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080282D4.c
 * Original SHA-256: 34c9bbcf940cffb60d0a6ac16deeff1e1c996410644fefa700240b7826ca07f8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* 080282D4..08028350: 124 bytes. */
struct Window {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 x, y, width, height;
    u16 tile;
    u8 field_16, kind;
    u16 color, style;
    u8 flags, field_1D, field_1E, field_1F;
    u16 field_20, field_22, field_24, field_26, field_28, field_2A;
};

struct WindowConfig {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 unknown_04;
    u16 tile;
    u16 unknown_08;
    u8 color;
    u8 style;
};

struct Dialog {
    u32 unknown_00;
    void *owner;
    u32 unknown_08;
    struct Window window;
    u8 unknown_38[0x48];
    struct WindowConfig config;
};

struct Options {
    u8 unknown_00[3];
    u8 enabled;
};

enum { WINDOW_CONTROL_MASK = 0xC00 };

struct ControlFlags { u16 display; };
extern struct ControlFlags g_control_flags_03000940;
extern struct Options *data_0200F438;
extern void func_08017490(struct Window *window, u8 x, u8 y,
                         u8 width, u8 height, u16 tile,
                         u16 color, u16 style, u8 kind);
extern void func_080282A4(struct Dialog *dialog);

void func_080282D4(struct Dialog *dialog)
{
    struct Window *window = &dialog->window;
    const struct WindowConfig *config = &dialog->config;

    g_control_flags_03000940.display |= WINDOW_CONTROL_MASK;
    func_08017490(window, config->x, config->y, config->width,
                 config->height, config->tile, config->color,
                 config->style, config->color == 0x32 ? 0xB : 0xC);
    if (dialog->owner != 0 && data_0200F438->enabled != 0)
        window->flags |= 1;
    func_080282A4(dialog);
}
