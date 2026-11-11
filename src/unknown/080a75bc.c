/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080A75BC.c
 * Original SHA-256: e1292bb4a8b571ac15d2ea0a70cd1a1a141154bcffe112b8ffd5e8d2a47d581d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct Unit080A75BC Unit080A75BC;
typedef struct {
    Unit080A75BC *unit;
    u32 unknown_04;
    s16 x, y, z;
    u8 unknown_0e[0x11];
    s8 layer;
} Node080A75BC;

typedef struct {
    Node080A75BC *node;
    u16 operation;
    u16 parameter;
    void *data;
} Entry080A75BC;

typedef struct {
    Entry080A75BC entries[16];
    u8 selected;
    u8 count;
    s8 timer;
    u8 flags;
    u16 state;
} Context080A75BC;

extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
/* The entry narrows its first two inputs to halfwords and stores input R2. */
extern void func_08025688(u16 operation, u16 parameter, void *data);
/* The entry consumes only the low byte of each coordinate. */
extern u8 func_0812F0E4(const Unit080A75BC *unit, s8 x, s8 z);
extern u8 func_080CD6A8(const void *unit);
extern s32 func_08025464(void);
extern void func_08141570(s32 player, u16 song);
extern void func_0809A298(Node080A75BC *node, u16 value, s8 layer);
extern u32 func_08099C64(const Node080A75BC *node);
extern void func_0809836C(Node080A75BC *node, u16 value, s8 layer, u16 mode);
extern void func_08029514(void);

/* 080A75BC..080A780C: 592 bytes including the six-way switch table.
 * Calls use the observed conditional ABI; no callee memory effects are assumed.
 */
u8 func_080A75BC(Context080A75BC *context, u16 buttons)
{
    switch (context->state) {
    case 0: {
        Node080A75BC *node = context->entries[context->selected].node;
        if (node) {
            func_08096F3C(node->x, node->y, node->z);
            context->state = 1;
        } else {
            context->state = 2;
        }
        break;
    }
    case 1:
        if (!func_08096F7C())
            context->state = 2;
        break;
    case 2: {
        u32 entry_offset = context->selected * sizeof(Entry080A75BC);
        Entry080A75BC *entry = (Entry080A75BC *)(entry_offset + (u32)context);
        Node080A75BC *node;
        func_08025688(entry->operation, entry->parameter, entry->data);
        context->timer = 0;
        context->flags = 0;
        node = context->entries[context->selected].node;
        if (!func_0812F0E4(node->unit, (s8)((u16)node->x >> 5),
                          (s8)((u16)node->z >> 5)) ||
            func_080CD6A8(context->entries[context->selected].node->unit))
            context->flags = 0xc0;
        context->state = 3;
        break;
    }
    case 3:
        ++context->timer;
        if (context->timer > 16 && (buttons & 3))
            context->timer = 120;
        if (context->timer >= 120)
            context->timer = 120;
        func_08025464();
        if (context->timer <= 120) {
            Entry080A75BC *entry = &context->entries[context->selected];
            if (entry->operation == 18 && !(context->flags & 0x40)) {
                if (!(context->flags & 0x80)) {
                    Node080A75BC *node;
                    func_08141570(1, 0x88);
                    node = context->entries[context->selected].node;
                    func_0809A298(node, 24, node->layer);
                    context->flags |= 0x80;
                } else {
                    s32 remaining = context->flags & ~0xc0;
                    if (remaining > 0)
                        break;
                    if (!func_08099C64(entry->node))
                        break;
                    ++remaining;
                    if (remaining > 0) {
                        Node080A75BC *node = context->entries[context->selected].node;
                        func_0809836C(node, 10, node->layer, 0);
                        remaining |= 0xc0;
                    }
                    context->flags = remaining;
                }
                break;
            }
            if (context->timer < 120)
                break;
        }
        if (context->entries[context->selected].operation == 18 &&
            !(context->flags & 0x40)) {
            Node080A75BC *node;
            if (!func_08099C64(context->entries[context->selected].node))
                break;
            node = context->entries[context->selected].node;
            func_0809836C(node, 10, node->layer, 0);
            context->flags |= 0x40;
        } else {
            func_08029514();
            context->state = 4;
        }
        break;
    case 4:
        if ((u16)func_08025464()) {
            ++context->selected;
            if (context->count <= context->selected)
                context->state = 5;
            else
                context->state = 0;
        }
        break;
    case 5:
        return 0;
    }
    return 1;
}
