/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0806617C.c
 * Original SHA-256: c83bacd329586a251c1761629fd3bf170d8781cbeb2555f2b32cd7cf2400b938
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 id;
    u8 quantity;
    u8 reference_quantity;
} Entry0806617C;

typedef struct {
    u8 unknown_000[0x0E];
    u16 count;
    u8 unknown_010[0x294];
    u8 blocks[0x180];
    Entry0806617C *entries[0];
} Table0806617C;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u16 flags;
    u8 appearance;
    u8 unknown_09[3];
    u16 blocks;
    u8 unknown_0E[2];
} Layout0806617C;

typedef struct Context0806617C {
    Table0806617C *table;
    u8 unknown_04[4];
    u8 mode;
    u8 handle;
    u8 unknown_0A;
    s8 selection;
    u8 unknown_0C[2];
    u8 flags;
    u8 unknown_0F[5];
    Layout0806617C layout;
    u8 window[0x74];
    s8 *enabled;
    void *tiles;
    void *temporary;
    u8 unknown_A4[0x10];
    u8 types[0];
} Context0806617C;

extern void (*const data_0836D4BC)(void *, const void *, u32);
extern void (*const data_0836D4C0)(void *, u32, u32);
extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern const Layout0806617C data_08393A24[];
extern const u8 data_08393AB4[];
extern void *func_08005B28(u32);
extern u32 func_0806807C(void);
extern u8 func_080680E0(void);
extern u8 func_080680F8(void);
extern u8 func_08068110(void);
extern u8 func_080C9540(u16);
extern u32 func_080D29D4(void *);
extern u32 func_080D2AD0(void *, s32, Entry0806617C **, s32);
extern s32 func_08067EE4(Entry0806617C **);
extern u32 func_08067F14(Entry0806617C **, u8);
extern u32 func_08067FB0(Entry0806617C **);
extern u32 func_08067FFC(Entry0806617C **);
extern void func_08068660(Context0806617C *);
extern u8 func_080C8310(Entry0806617C *);
extern u8 func_080C82D8(Entry0806617C *);
extern u32 func_08013B50(Layout0806617C *);
extern void func_08017490(void *, u8, u8, u8, u8, u16, u16, u16, u8);
extern void func_08013B7C(const Layout0806617C *, void *, const void *);
extern void func_08016C90(void *, u8);
extern u8 func_08066DDC(Context0806617C *);
extern u8 func_080098F4(u8 (*)(Context0806617C *), Context0806617C *);

/* Complete [0x0806617C, 0x080664C4): 840 bytes, 339 instructions. */
void func_0806617C(Context0806617C *context)
{
    Layout0806617C *layout = &context->layout;
    void *window;
    u8 available;

    data_0836D4BC(layout, &data_08393A24[context->mode], sizeof(*layout));
    context->enabled = func_08005B28(layout->count);
    data_0836D4C0(context->enabled, layout->count, 1);
    g_callbacks_0836D4B8[0](context->table->entries, 0x5E0);
    context->table->count = 0;

    switch (context->mode) {
    case 1:
        if ((u8)(func_0806807C() | func_080680E0()) == 0) {
            available = func_080C9540(0x207);
            if (!available || !(available = func_080680F8()))
                context->enabled[1] = available;
        }
        available = func_08068110();
        if (!available)
            context->enabled[2] = available;
        break;
    case 2:
        available = func_0806807C();
        if (!available)
            context->enabled[0] = available;
        available = func_080680E0();
        if (!available)
            context->enabled[1] = available;
        available = func_080C9540(0x207);
        if (!available || !(available = func_080680F8()))
            context->enabled[2] = available;
        break;
    case 3:
        context->temporary = func_08005B28(0xC0);
        g_callbacks_0836D4B8[0](context->temporary, 0xC0);
        context->table->count = func_080D29D4(context->temporary);
        context->table->count = func_080D2AD0(context->temporary, 12,
                                             context->table->entries, 12);
        layout->count = context->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 6)
            layout->y = data_08393AB4[layout->count - 1];
        break;
    case 5: {
        s32 i;
        context->table->count = func_08067EE4(context->table->entries);
        layout->count = context->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        for (i = 0; i < context->table->count; i++) {
            if (*(u16 *)((u8 *)context->table->entries[i] + 2) != 0)
                context->enabled[i] = -1;
        }
        if (layout->count <= 7)
            layout->y = data_08393AB4[layout->count - 1];
        break;
    }
    case 4: {
        s32 i;
        func_08068660(context);
        context->table->count = func_08067F14(context->table->entries,
                                             context->types[context->selection]);
        layout->count = context->table->count;
        for (i = 0; i < context->table->count; i++) {
            Entry0806617C *entry = context->table->entries[i];
            if (entry->reference_quantity == entry->quantity)
                context->enabled[i] = 0;
        }
        break;
    }
    case 6:
        context->table->count = func_08067FB0(context->table->entries);
        layout->count = context->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        if (layout->count <= 7)
            layout->y = data_08393AB4[layout->count - 1];
        break;
    case 7: {
        s32 i;
        context->table->count = func_08067FFC(context->table->entries);
        for (i = 0; i < context->table->count; i++) {
            Entry0806617C *entry = context->table->entries[i];
            if (func_080C8310(entry) || func_080C82D8(entry))
                context->enabled[i] = 0;
        }
        layout->count = context->table->count;
        if (layout->count < layout->height)
            layout->height = layout->count;
        break;
    }

    }

    window = context->window;
    context->tiles = func_08005B28(func_08013B50(layout));
    func_08017490(window, layout->x, layout->y, layout->width, layout->height,
                 layout->flags, 5, 1, 12);
    func_08013B7C(layout, window, context->table->blocks);
    func_08016C90(window, layout->appearance);
    context->flags = 0;
    context->handle = func_080098F4(func_08066DDC, context);
}
