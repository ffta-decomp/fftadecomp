/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08026B90.c
 * Original SHA-256: 25ca5d06765c7ba70506d9763388c612ca4092cf38b69bad38d08d933e27b480
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xc];
    u8 visible_entries;
    u8 state;
    u8 unknown_0e[6];
} MenuState;

typedef struct {
    u8 unknown_00[0x80];
    MenuState menu;
    s32 *indices;
    u8 *enabled;
} MenuContext;

typedef struct {
    u8 unknown_00[4];
    u16 id;
    u8 type;
    u8 unknown_07;
} MenuEntry;

typedef struct {
    MenuEntry *entries;
    u8 first;
    u8 last;
    u8 kind;
    u8 width;
    u8 severity;
    u8 count;
} MenuList;

typedef struct {
    u16 name;
    u8 unknown_02[26];
} ResourceEntry;

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[0x18];
    Unit *unit;
} BattleContext;

extern BattleContext *data_0200F438;
extern const ResourceEntry data_0855187C[];
extern const void *g_table_085567F0[];
extern u32 func_080CB388(u32 index);
extern u32 func_080CB2B4(u32 id);
extern u32 func_080CD95C(Unit *unit);
extern u32 func_080C95A8(u32 value);
extern u32 func_080CCD50(u32 id, u32 category);
extern u32 func_080161BC(const void *text);
extern u32 func_080269D8(Unit *unit);
extern u32 func_08026A30(Unit *unit);

/* Complete target: [0x08026B90, 0x08026D44), 436 bytes. */
void func_08026B90(MenuContext *context, MenuList *list)
{
    MenuState *menu = &context->menu;
    s32 i = 1;
    s32 count = 0;
    MenuEntry *entry;
    u8 width;

    for (; i <= 14; i++) {
        u16 id;

        entry = &list->entries[i];
        id = func_080CB388((u8)i);
        if ((u8)func_080CB2B4(id)) {
            context->indices[count] = i;
            if ((u8)func_080CD95C(data_0200F438->unit) && id != 0x172) {
                context->enabled[count] = 0;
            } else if ((u8)func_080C95A8(13) == 1 && func_080CCD50(entry->id, 31) == 0) {
                context->enabled[count] = 0;
            }
            count++;
            {
                u32 offset = entry->id * sizeof(ResourceEntry);
                const ResourceEntry *resource = (const ResourceEntry *)((const u8 *)data_0855187C + offset);
                width = func_080161BC(g_table_085567F0[resource->name]);
            }
            if (width > list->width)
                list->width = width;
        }
    }

    context->indices[count] = 15;
    entry = &list->entries[15];
    if ((u8)func_080C95A8(13) == 1 && func_080CCD50(entry->id, 31) == 0) {
        context->enabled[count] = 0;
    } else if ((u8)func_080CD95C(data_0200F438->unit) ||
               !(u8)func_080269D8(data_0200F438->unit) ||
               !(u8)func_08026A30(data_0200F438->unit)) {
        context->enabled[count] = 0;
    }
    count++;
    {
        u32 offset = entry->id * sizeof(ResourceEntry);
        const ResourceEntry *resource = (const ResourceEntry *)((const u8 *)data_0855187C + offset);
        width = func_080161BC(g_table_085567F0[resource->name]);
    }
    if (width > list->width)
        list->width = width;

    if (count != 1) {
        list->severity = 2;
        menu->visible_entries = 15;
        menu->state = 8;
    }
    list->count = count;
}
