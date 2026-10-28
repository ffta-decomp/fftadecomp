/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08042030.c
 * Original SHA-256: 46f408fbbf90a88380f40d76b1d3626e63474b2b969f452eb366cc9033b220a7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s32 count;
} MenuData;

typedef struct {
    u8 unknown_00[0x1a];
    u16 selection;
    u8 unknown_1c[0x2c];
} MenuList;

typedef struct {
    u8 unknown_00[0x30];
    u16 object_id;
    u8 unknown_32[0x16];
    MenuData *data;
    u8 panel[0x2c];
    MenuList list;
    const void *resource;
    u8 unknown_c4[8];
} MenuRecord;

typedef struct {
    u8 unknown_00[0x954];
    MenuRecord records[1];
} MenuContext;

typedef struct {
    u8 unknown_00[0x0e];
    u16 height;
    u8 unknown_10[0x3c];
} RenderObject;

typedef void (*MenuCallback)(void);

extern MenuContext *g_state_03002810;
extern RenderObject data_030009E0[];
extern void func_08016210(u8 *panel, const void *resource, u16 height, u16 count);
extern u32 func_08017B50(MenuList *list);
extern void func_08042024(MenuList *list);
extern void func_08041BB0(s32 slot, s16 item, MenuList *list);
extern void func_08041FB4(MenuList *list, u16 selection);
extern void func_08037F74(u8 *panel, MenuCallback primary, MenuCallback secondary,
                         u32 option, u32 command);
extern void func_08038024(void);
extern void func_08038028(void);
extern void func_08038238(void);

/* Complete target: [0x08042030, 0x08042148), 280 bytes. */
void func_08042030(s32 slot)
{
    u16 object_id = g_state_03002810->records[slot].object_id;
    u16 count;
    s32 item;

    func_08016210(g_state_03002810->records[slot].panel,
                  g_state_03002810->records[slot].resource,
                  data_030009E0[object_id].height,
                  g_state_03002810->records[slot].data->count);
    count = func_08017B50(&g_state_03002810->records[slot].list);
    func_08042024(&g_state_03002810->records[slot].list);
    for (item = 0; item < count; item++)
        func_08041BB0(slot, item, &g_state_03002810->records[slot].list);
    func_08041FB4(&g_state_03002810->records[slot].list,
                  g_state_03002810->records[slot].list.selection * 2);
    if (g_state_03002810->records[slot].data->count > 0)
        func_08037F74(g_state_03002810->records[slot].panel,
                      func_08038028, func_08038238, 0, 13);
    else
        func_08037F74(g_state_03002810->records[slot].panel,
                      func_08038024, func_08038238, 0, 13);
}
