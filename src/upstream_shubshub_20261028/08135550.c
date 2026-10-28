/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08135550.c
 * Original SHA-256: 1fed4410f3906d422d924522a2fe0d9b7824255317a7852f0e09979dfd0a5127
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TableEntry08135550 {
    u32 unknown_00[3];
    u8 kind;
};

struct Record08135550 {
    u8 unknown_00;
    u8 kind;
};

struct Root08135550 {
    u8 unknown_00[0x3c34];
    u16 selection_ids[0];
};

struct State08135550 {
    void *source;
    void *target;
    u8 unknown_08[0x1e];
    u16 flags;
    u8 unknown_28[8];
    struct Record08135550 *record;
};

extern struct Root08135550 g_state_02000000;
extern const struct TableEntry08135550 g_table_08528F34[];
extern struct State08135550 data_0200F3F0;
extern void func_0812F2A4(u16 entry, void *first, void *second);
extern void func_0812F328(u8 index);
extern u8 func_08130FBC(void);
extern u8 func_08131378(void);
extern void func_0812F34C(void *target);
extern void func_0812F39C(s32 index);
extern u8 func_080C8280(const void *object);

/* Target: [0x08135550, 0x08135624), 212 bytes, 90 instructions. */
u32 func_08135550(void *source, void *target, u16 entry,
                  const u8 *options, u8 selection)
{
    u16 table_index;
    const struct TableEntry08135550 *selected_entry;

    if (selection == 0)
        return 0;
    table_index = g_state_02000000.selection_ids[selection - 1];
    selected_entry = g_table_08528F34 + table_index;
    switch (selected_entry->kind) {
    case 2:
    case 3:
        if (target == 0 || entry == 0)
            break;
        func_0812F2A4(entry, 0, 0);
        data_0200F3F0.flags |= 0x10;
        data_0200F3F0.source = source;
        data_0200F3F0.target = target;
        {
            s32 i;

            for (i = 0; i < 3; i++) {
                func_0812F328(i);
                if (func_08130FBC() && func_08131378()) {
                    func_0812F34C(target);
                    func_0812F39C(i);
                    if (data_0200F3F0.record->kind == 0x3b)
                        return 3;
                }
            }
        }
    case 1:
        if (target != 0 && options != 0) {
            s32 flags = *options;

            if (((flags >> 6) & 1) || func_080C8280(target))
                return 3;
        }
        break;
    }
    return 1;
}
