/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080651FC.c
 * Original SHA-256: 2d950ae754fe6212a3829519536da172a4bc21cb063d64c32ff0f69cb6267253
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct { u16 selection, position; } SavedTab080651FC;
typedef struct {
    u8 unknown_000[0x424];
    void *entries[0x178];
    SavedTab080651FC tabs[8];
    u8 unknown_A24[0x130];
    u8 control_flags[0x50];
    u8 *backup_first;
    u8 *backup_second;
} Saved080651FC;
typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 selection;
} Cursor080651FC;
typedef struct {
    Saved080651FC *saved;
    u16 flags;
    s16 result;
    u8 mode;
    u8 unknown_09[7];
    void *task;
    u8 unknown_14[0x3C];
    Cursor080651FC cursor;
    u8 unknown_6C[0x15];
    s8 position;
} Context080651FC;
typedef struct {
    u16 state;
    u8 unknown_02[0x12];
    u16 mode;
} Event080651FC;
typedef struct { u8 unknown_00[0x10]; const void *first, *second; } Graphics080651FC;
typedef struct { u8 unknown_000[0x1090]; s8 status; } TaskData080651FC;

extern Saved080651FC *data_0200F454;
extern u8 g_control_flags_03000940[];
extern void *data_030027F4;
extern u32 data_030027D4;
extern Graphics080651FC data_03000990;
extern u8 g_state_0200F390;
extern u8 data_02003CB0[];
extern const u8 data_083B53A4[];
extern u8 data_06012700[];
extern void func_0806617C(Context080651FC *);
extern u8 func_080664E0(Context080651FC *);
extern u8 func_08068808(const Context080651FC *);
extern int func_08068810(Context080651FC *);
extern u32 func_08066694(Context080651FC *);
extern u8 func_080667E4(Context080651FC *);
extern void func_080665B0(Context080651FC *);
extern void func_08066A8C(Context080651FC *);
extern void func_08068820(Context080651FC *);
extern void func_080664C4(Context080651FC *);
extern void func_080651C8(void *);
extern void func_080687D8(Context080651FC *);
extern u8 func_08066570(Context080651FC *);
extern void *func_08005BFC(void *);
extern u32 func_08005BB0(const void *);
extern void func_08005B58(void *);
extern void *func_081443FC(void *, const void *, u32);
extern u16 func_08017B68(Cursor080651FC *, u32);
extern void *func_08022840(u32);
extern void func_08022854(u8 *);
extern void func_0814186C(const void *, void *, u32);
extern void func_08022E90(u16, u8);
extern void func_080C7214(void);
extern u8 *func_0800543C(void *, const void *);
extern void func_080C71B4(u16);
extern void func_08068864(Context080651FC *);

/* Complete target [0x080651FC, 0x08065608): 1036 bytes, 406 instructions. */
u32 func_080651FC(void *task, Event080651FC *event, Context080651FC *context)
{
    switch (event->state) {
    case 0:
        context->mode = event->mode;
        context->saved = data_0200F454;
        break;
    case 3:
        break;
    case 0x100:
        func_0806617C(context);
        event->state = 0x102;
        break;
    case 0x102:
        if (func_080664E0(context)) {
            if (func_08068808(context)) {
                event->state = 0x106;
            } else if ((u8)func_08068810(context)) {
                event->state = 0x10B;
            } else {
                event->state = 0x104;
            }
        }
        break;
    case 0x111:
        if ((u8)func_08066694(context))
            event->state = 0x104;
        break;
    case 0x104:
        if (func_080667E4(context)) {
            switch (context->result) {
            case -3:
                context->result = 0;
                event->state = 0x107;
                break;
            case -4:
                context->result = 0;
                event->state = 0x10E;
                break;
            case -6:
                func_080665B0(context);
                context->result = 0;
                event->state = 0x111;
                break;
            default: {
                SavedTab080651FC *tab = &context->saved->tabs[context->mode];
                tab->selection = context->cursor.selection;
                tab->position = (u8)context->position;
                event->state = 0x106;
                break;
            }
            }
        }
        func_08066A8C(context);
        break;
    case 0x107:
        func_08068820(context);
        func_08066A8C(context);
        event->state = 0x104;
        break;
    case 0x106:
        if (context->flags & 0x80) {
            func_080664C4(context);
            context->flags &= 0xFF7F;
            event->state = 3;
        } else if (context->flags & 0x40) {
            if (context->task) {
                func_080651C8(task);
                event->state = 0x10C;
            } else {
                context->flags &= 0xFFBF;
                func_080687D8(context);
                event->state = 0x103;
            }
        } else if (context->flags & 0x20) {
            context->flags &= 0xFFDF;
            event->state = 0x104;
        }
        break;
    case 0x103:
        if (func_08066570(context)) {
            context->result = -2;
            event->state = 0x106;
        }
        break;
    case 0x10B:
        if (((TaskData080651FC *)func_08005BFC(context->task))->status == 1)
            event->state = 0x104;
        break;
    case 0x10C:
        if (func_08005BB0(context->task)) {
            func_08005B58(context->task);
            context->task = 0;
            context->flags &= 0xFFBF;
            func_080687D8(context);
            event->state = 0x103;
        }
        break;
    case 0x10E:
        func_081443FC(context->saved->control_flags, g_control_flags_03000940, 0x50);
        data_030027F4 = context->saved->entries[func_08017B68(&context->cursor, context->position)];
        data_030027D4 = 0;
        context->saved->backup_first = func_08022840(0x6C00);
        context->saved->backup_second = func_08022840(0x1000);
        func_0814186C(data_03000990.first, context->saved->backup_first, 0x3600);
        func_0814186C(data_03000990.second, context->saved->backup_second, 0x800);
        func_08022E90(4, 16);
        g_state_0200F390 = 0x1B;
        func_080C7214();
        event->state = 0x10F;
        break;
    case 0x10F:
        if (g_state_0200F390 == 0x20) {
            func_0814186C(context->saved->backup_first, (void *)data_03000990.first, 0x3600);
            func_0814186C(context->saved->backup_second, (void *)data_03000990.second, 0x800);
            func_08022854(context->saved->backup_first);
            func_08022854(context->saved->backup_second);
            func_081443FC(g_control_flags_03000940, context->saved->control_flags, 0x50);
            func_0800543C(data_02003CB0, data_083B53A4);
            func_0814186C(data_02003CB0 + 0x300, data_06012700, 0x80);
            func_080C71B4(3);
            event->state = 0x110;
        }
        break;
    case 0x110:
        if (g_state_0200F390 == 0)
            event->state = 0x104;
        break;
    }
    if (event->state > 0x101)
        func_08068864(context);
    return 0;
}
