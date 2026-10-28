/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080426A4.c
 * Original SHA-256: d2022ace9a3ad00b9bbe06d242fce2ffbeed4a1057318e952df43ecaf19f3a41
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} Cursor080426A4;

typedef struct {
    u8 unknown_00[0x78];
    u8 list[0x20];
    Cursor080426A4 cursor;
    u8 settings[0x14];
    u8 unknown_c0[0x0c];
} Slot080426A4;

typedef struct {
    u8 unknown_000[0x954];
    Slot080426A4 slots[1];
} State080426A4;

extern State080426A4 *g_state_03002810;
extern void func_08017FBC(void *, u32);
extern u16 func_08017B68(void *, u32);
extern void func_08017AF4(void *, u32, u32);
extern void func_08017FB0(Cursor080426A4 *, u8);
extern void func_08037DF0(u32, s32);
extern void func_08042D4C(u32, s16, void *);
extern void func_08017884(void *, u32, u32);

/* 0x080426A4..0x08042774: 208 bytes, 88 instructions. */
void func_080426A4(u32 index, u8 option, u8 row, u8 refresh)
{
    s8 selected;

    func_08017FBC(g_state_03002810->slots[index].settings, option);
    selected = row;
    func_08017B68(g_state_03002810->slots[index].list, selected);
    if (!refresh) {
        func_08017AF4(g_state_03002810->slots[index].list, selected, 11);
        func_08017FB0(&g_state_03002810->slots[index].cursor, (u8)selected);
        func_08037DF0(index, selected);
    } else {
        func_08042D4C(index, selected, g_state_03002810->slots[index].list);
        func_08037DF0(index, selected);
        func_08017884(g_state_03002810->slots[index].list, option, 1);
        func_08017AF4(g_state_03002810->slots[index].list,
                      (s8)g_state_03002810->slots[index].cursor.row, 11);
    }
}
