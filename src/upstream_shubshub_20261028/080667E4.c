/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080667E4.c
 * Original SHA-256: 6fd4bd0c7a46c178e865a914ef98917362f9e16d5bcaa1cd380f1fbf9e4868d1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080667E4..0x080669B2: 462 bytes. */
typedef struct {
    u16 selection;
    u16 position;
} SavedTab;

typedef struct {
    u8 unknown_00[9];
    u8 tab;
    u8 unknown_0a[2];
    u16 count;
    u8 unknown_0e[0xA16];
    SavedTab tabs[4];
} SavedMenu;

typedef struct {
    u8 unknown_00[0x1A];
    u16 selection;
    u8 unknown_1c[4];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x0A];
    u16 first;
    u8 unknown_0c[2];
    u16 second;
    u8 flags;
    s8 position;
} MenuPanel;

typedef struct {
    SavedMenu *saved;
    u16 flags;
    u16 result;
    u8 mode;
    u8 unknown_09[2];
    s8 tab;
    u8 unknown_0c;
    u8 confirmed;
    u8 unknown_0e[2];
    void *widget;
    u8 unknown_14[0x3C];
    MenuCursor cursor;
    MenuPanel panel;
    u8 unknown_84[0x14];
    s8 *availability;
} MenuContext;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} WidgetState;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

extern InputState data_03000000;
extern u16 func_08017B68(MenuCursor *cursor, s8 position);
extern u16 func_08066718(MenuContext *context, s16 selection);
extern WidgetState *func_08005BFC(void *widget);
extern void func_08141570(u32 channel, u32 sound);
extern void func_08141540(u32 sound);
extern void func_08017D18(MenuPanel *panel, u32 mode);
extern u32 func_08067B80(MenuContext *context, u16 pressed, u16 repeated, u16 held);
extern u32 func_08067A40(MenuContext *context, u16 pressed, u16 repeated, u16 held);

u8 func_080667E4(MenuContext *context)
{
    MenuPanel *panel = &context->panel;
    u16 pressed = data_03000000.pressed;
    u16 repeated = data_03000000.repeated;
    u16 held = data_03000000.held;
    u16 cancel;
    u32 result;

    if (pressed & 4) {
        context->saved->count = func_08066718(context,
            (s16)func_08017B68(&context->cursor, context->panel.position));
        if (context->saved->count) {
            --context->saved->count;
            context->result = 0xFFFA;
            return 1;
        }
    }
    cancel = pressed & 2;
    if (cancel) {
        if (context->mode == 4) {
            SavedTab *tab = &context->saved->tabs[context->tab];

            tab->selection = context->cursor.selection;
            tab->position = (u8)panel->position;
            context->saved->tab = context->tab;
            if (context->widget && (func_08005BFC(context->widget)->flags & 4)) {
                context->result = 0xFFFC;
                return 1;
            }
        }
        func_08141570(1, 0x69);
        context->confirmed = 0;
        if (panel->flags & 1)
            func_08017D18(panel, 1);
        context->result = 0xFFFF;
        return 1;
    } else if (pressed & 1) {
        u16 selection = func_08017B68(&context->cursor, panel->position);
        s16 index;

        if (context->mode == 4) {
            SavedTab *tab = &context->saved->tabs[context->tab];

            tab->selection = context->cursor.selection;
            tab->position = (u8)panel->position;
            context->saved->tab = context->tab;
        }
        index = selection;
        if (context->availability[index] <= 0) {
            func_08141570(1, 0x6B);
            return 0;
        }
        context->confirmed = 0;
        func_08141540(0x64);
        context->result = index + 1;
        if (panel->flags & 1) {
            if (panel->first + panel->second <= 0x3F)
                func_08017D18(panel, 0);
            else
                func_08017D18(panel, 1);
        }
        return 1;
    } else if (context->widget && (pressed & 0x100)) {
        context->result = 0xFFFC;
        return 1;
    }
    if (context->flags & 8)
        return 0;
    if (!(context->flags & 0x10))
        result = func_08067B80(context, pressed, repeated, held);
    else
        result = func_08067A40(context, pressed, repeated, held);
    return result;
}
