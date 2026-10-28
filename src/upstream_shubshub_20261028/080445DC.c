/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080445DC.c
 * Original SHA-256: fd22a3880a8a09429688133b3561bc7fb33e01b3116faebce445b8c25a2d8801
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct EntrySpecification {
    u8 slot : 3;
    u8 unknown_03 : 1;
    u8 mode : 2;
    u8 type : 4;
    u8 unknown_0a : 6;
    u8 position : 5;
    u8 unknown_15 : 2;
    u8 resource : 8;
    u8 unknown_1f : 1;
} __attribute__((packed));

struct MenuEntry {
    u16 active : 1;
    u16 pending : 1;
    u16 changed : 1;
    u16 mode : 3;
    u16 type : 4;
    u16 unknown_0a : 3;
    u16 option : 1;
    u16 unknown_0e : 2;
    u8 unknown_02;
    u8 slot;
    u8 unknown_04;
    u8 resource;
    u8 value;
    u8 next;
    u8 unknown_08;
    u8 details[0x2B];
};

struct MenuContext {
    u8 unknown_000[0x7B8];
    struct MenuEntry entries[8];
};

extern struct MenuContext *g_state_03002810;
extern u8 func_08045424(u8 resource);
extern u8 func_0804BB5C(u8 slot, u8 resource, u8 *details);
extern void func_08045390(u8 index);

/* Complete target: [0x080445DC, 0x08044770), 404 bytes. */
u32 func_080445DC(struct EntrySpecification *specification, u8 slot,
                  u32 unused, u8 option)
{
    u8 index;

    if (g_state_03002810->entries[specification->slot].active)
        return 0;
    index = specification->slot;
    g_state_03002810->entries[index].changed = 1;
    g_state_03002810->entries[index].active = 1;
    g_state_03002810->entries[index].pending = 0;
    g_state_03002810->entries[index].option = option;
    g_state_03002810->entries[index].slot = slot;
    g_state_03002810->entries[index].mode = specification->mode + 1;
    g_state_03002810->entries[index].type = specification->type;
    if (g_state_03002810->entries[index].type == 2 ||
        g_state_03002810->entries[index].type == 4) {
        g_state_03002810->entries[index].resource =
            func_08045424(specification->resource);
        if (g_state_03002810->entries[index].type == 2 ||
            g_state_03002810->entries[index].type == 4) {
            g_state_03002810->entries[index].value = func_0804BB5C(
                g_state_03002810->entries[index].slot,
                g_state_03002810->entries[index].resource,
                g_state_03002810->entries[index].details);
            g_state_03002810->entries[index + 1].next = 0;
        }
    }
    func_08045390(index);
    return index;
}
