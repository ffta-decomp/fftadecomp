/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0803AD08.c
 * Original SHA-256: eedb01cdc34ea46a3b0e5d0612222533d34f64b05667ba9cda864bb4166a31cb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 x;
    u8 y;
    u8 first0, second0;
    u8 unknown_04[2];
    u8 first1, second1;
    u8 unknown_08[2];
    u8 first2, second2;
    u8 unknown_0C[2];
    u8 first3, second3;
    u8 unknown_10[4];
} LinkRecord;

typedef struct {
    u8 unknown_00[3];
    u8 record;
    u8 unknown_04[8];
} MapEntry;

typedef struct {
    u8 unknown_000[0xB0];
    MapEntry entries[1];
} EntryMap;

typedef struct {
    const EntryMap *map;
    u8 unknown_004[0x678];
    LinkRecord *records;
} LinkState;

extern LinkState *g_state_03002810;
extern const u8 data_08391CA4[];
extern u8 func_080363C0(u8 identifier, const u8 *map);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete owner: 0x0803AD08..0x0803AE80, 376 bytes. */
u32 func_0803AD08(u32 entry, u8 *indices, u8 *values)
{
    u32 count = 0;
    u8 record;
    u32 found;
    u8 link;
    u16 clear_indices = 0;
    u16 clear_values;

    func_0814186C(&clear_indices, indices, 0x01000002);
    clear_values = 0;
    func_0814186C(&clear_values, values, 0x01000002);
    record = g_state_03002810->map->entries[entry].record - 1;

    link = g_state_03002810->records[record].second0;
    if (link || g_state_03002810->records[record].first0) {
        found = func_080363C0(link + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    link = g_state_03002810->records[record].second1;
    if (link || g_state_03002810->records[record].first1) {
        found = func_080363C0(link + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    link = g_state_03002810->records[record].second2;
    if (link || g_state_03002810->records[record].first2) {
        found = func_080363C0(link + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    link = g_state_03002810->records[record].second3;
    if (link || g_state_03002810->records[record].first3) {
        found = func_080363C0(link + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    return count;
}
