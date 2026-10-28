/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08040E30.c
 * Original SHA-256: 18463f84b2d3f8923f4b6940669d3d56414fbcb7ef5527a758b369dd538ab391
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s32 count;
    u8 unknown_04[4];
    u8 option;
} MenuData;

typedef struct {
    u8 unknown_00[0x30];
    u16 object_id;
    u8 unknown_32[0x16];
    MenuData *data;
    u8 panel[0x2c];
    u8 list[0x48];
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
extern u32 func_08017B50(u8 *list);
extern void func_08040B70(s32 slot, s16 item, u8 *list);
extern void func_08040E14(u16 object_id, u8 *list);
extern void func_08037F74(u8 *panel, MenuCallback primary, MenuCallback secondary,
                         u32 option, u32 command);
extern void func_08038024(void);
extern void func_08038028(void);
extern void func_08038238(void);

/* Complete target: [0x08040E30, 0x08040F38), 264 bytes. */
void func_08040E30(s32 slot)
{
    u16 object_id = g_state_03002810->records[slot].object_id;
    u16 count;
    s32 item;
    u8 option;

    func_08016210(g_state_03002810->records[slot].panel,
                  g_state_03002810->records[slot].resource,
                  data_030009E0[object_id].height,
                  g_state_03002810->records[slot].data->count);
    count = func_08017B50(g_state_03002810->records[slot].list);
    for (item = 0; item < count; item++)
        func_08040B70(slot, item, g_state_03002810->records[slot].list);
    func_08040E14(object_id, g_state_03002810->records[slot].list);
    option = g_state_03002810->records[slot].data->option;
    if (g_state_03002810->records[slot].data->count > 0)
        func_08037F74(g_state_03002810->records[slot].panel,
                      func_08038028, func_08038238, option, 13);
    else
        func_08037F74(g_state_03002810->records[slot].panel,
                      func_08038024, func_08038238, option, 13);
}
