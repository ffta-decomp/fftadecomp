/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08042148.c
 * Original SHA-256: 96f505f210f3136be7fc8df3ebafd6d11240b3a23205f84f5f9389b0cef245db
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x48];
} MenuList;

typedef struct {
    u8 unknown_00[0x78];
    MenuList list;
    u8 unknown_C0[0x0C];
} MenuRecord;

typedef struct {
    u8 unknown_000[0x954];
    MenuRecord records[1];
} MenuContext;

extern MenuContext *g_state_03002810;
extern u32 func_08017B50(MenuList *list);
extern void func_08041BB0(s32 slot, s16 item, MenuList *list);

/* Complete target: [0x08042148, 0x080421A4), 92 bytes, 38 instructions. */
void func_08042148(s32 slot)
{
    u16 count = func_08017B50(&g_state_03002810->records[slot].list);
    s32 item;

    for (item = 0; item < count; item++)
        func_08041BB0(slot, item, &g_state_03002810->records[slot].list);
}
