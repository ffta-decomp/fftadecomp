/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080675A0.c
 * Original SHA-256: 53d20d37985fb11f5b4b4d377dbc1d8eb7cba9d12d4f28aa2c23c9c7617dfa9e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 second;
    u8 first;
} Entry080675A0;

typedef struct {
    u8 unknown_000[0x424];
    Entry080675A0 *entries[0];
} Table080675A0;

typedef struct {
    u8 unknown_00[2];
    u8 row;
} Row080675A0;

typedef struct {
    Table080675A0 *table;
    u8 unknown_04[7];
    s8 selection;
    u8 unknown_0c[8];
    Row080675A0 position;
    u8 unknown_18[0x80];
    u8 *flags;
    u8 unknown_9c[8];
    u8 text[0x10];
    u8 types[0];
} State080675A0;

extern const u8 *g_table_08526680[];
extern const u8 data_083A9CA4[];
extern void func_08018C24(void *, const void *);
extern void func_080142DC(void *, u32, u32);
extern void func_08015110(void *, void *, const void *, u32, u32);
extern void *func_08005B28(u32);
extern void func_08005318(const void *, void *, u32, u32);
extern void func_0814186C(const void *, void *, u32);
extern void func_08005B40(void *);

/* Complete [0x080675A0, 0x080676F8): 344 bytes, 155 instructions. */
void func_080675A0(State080675A0 *state, void *context, u8 *tiles, u16 index)
{
    Row080675A0 *position = &state->position;
    Entry080675A0 *entry = state->table->entries[index];
    u8 digits;
    void *temporary;

    if (state->types[state->selection] == 5) {
        digits = 3;
        func_08018C24(state->text, g_table_08526680[0]);
    } else {
        digits = entry->first <= 9 ? 1 : 2;
        func_080142DC(state->text, entry->first, digits);
    }
    tiles += (position->row - 10) * 0x40;
    if (digits == 1)
        tiles += 0x40;
    {
        s32 flag = (s8)state->flags[index];

        if (flag == 0)
            func_08015110(context, tiles, state->text, 1, 1);
        else
            func_08015110(context, tiles, state->text, 0, 1);
    }

    tiles += 0x40;
    if (digits == 2 || digits == 3)
        tiles += 0x40;
    temporary = func_08005B28(0x40);
    func_08005318(data_083A9CA4, temporary, 0x20, 1);
    func_0814186C(temporary, tiles, 0x20);
    func_08005B40(temporary);

    tiles += 0x40;
    digits = entry->second <= 9 ? 1 : 2;
    func_080142DC(state->text, entry->second, digits);
    if (digits == 1)
        tiles += 0x40;
    {
        s32 flag = (s8)state->flags[index];

        if (flag == 0)
            func_08015110(context, tiles, state->text, 1, 1);
        else
            func_08015110(context, tiles, state->text, 0, 1);
    }
}
