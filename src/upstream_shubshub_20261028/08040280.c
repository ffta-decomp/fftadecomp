/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08040280.c
 * Original SHA-256: 7a00adf08ae71f07f1b071088e5367deed811200192481a803a904b692b11104
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Info08040280 {
    union {
        s32 count;
        u16 halves[2];
    } value;
    u8 unknown_04[4];
    u8 option;
};

struct Record08040280 {
    u8 unknown_00[0x30];
    u16 id;
    u8 unknown_32[0x16];
    struct Info08040280 *info;
    u8 first[0x2c];
    u8 second[0x48];
    const void *text;
    u8 unknown_c4[8];
};

struct State08040280 {
    u8 unknown_000[0x954];
    struct Record08040280 records[1];
};

struct Unit08040280 {
    u8 unknown_00[0xe];
    u16 value;
    u8 unknown_10[0x3c];
};

typedef void (*Callback08040280)(void);

extern struct State08040280 *g_state_03002810;
extern struct Unit08040280 data_030009E0[];
extern void func_08016210(u8 *, const void *, u32, u32);
extern u32 func_08017B50(u8 *);
extern void func_0803FF9C(s32, s16, u8 *);
extern void func_08040264(u32, u8 *);
extern void func_08037F74(u8 *, Callback08040280, Callback08040280, u32, u32);
extern void func_08038028(void);
extern void func_08038024(void);
extern void func_08038238(void);

/* Target: [0x08040280, 0x08040388), 264 bytes, 106 instructions. */
void func_08040280(s32 index)
{
    u32 id = g_state_03002810->records[index].id;
    s32 count;
    s32 i;
    struct Info08040280 *info;
    u8 option;

    func_08016210(g_state_03002810->records[index].first,
                 g_state_03002810->records[index].text,
                 data_030009E0[id].value,
                 g_state_03002810->records[index].info->value.halves[0]);
    count = (u16)func_08017B50(g_state_03002810->records[index].second);
    for (i = 0; i < count; i++)
        func_0803FF9C(index, i, g_state_03002810->records[index].second);
    func_08040264(id, g_state_03002810->records[index].second);
    info = g_state_03002810->records[index].info;
    option = info->option;
    if (info->value.count > 0) {
        func_08037F74(g_state_03002810->records[index].first,
                     func_08038028, func_08038238, option, 13);
    } else {
        func_08037F74(g_state_03002810->records[index].first,
                     func_08038024, func_08038238, option, 13);
    }
}
