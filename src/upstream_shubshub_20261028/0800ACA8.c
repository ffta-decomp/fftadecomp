/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800ACA8.c
 * Original SHA-256: 5aa9579ab53a3676e16aafca1c065b13da1d347fda0b3ecff391e989ab029bfd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Table0800ACA8 {
    u16 unknown_00;
    u16 flags;
    u16 unknown_04;
    s16 current;
    u8 unknown_08[0x10];
    const u8 *data;
};

static inline u16 read_le16_0800ACA8(const u8 *data)
{
    u32 low = data[0];

    return (data[1] << 8) | low;
}

/* Target: [0x0800ACA8, 0x0800ADD8), 304 bytes, 152 instructions. */
void func_0800ACA8(struct Table0800ACA8 *table, s16 index,
                   u16 *first, u16 *second, u16 *third, u16 *fourth)
{
    if (index == -1)
        index = table->current;
    if (table->flags & 8) {
        if (table->flags & 0x8000) {
            const u8 *entry = table->data + (index * 6 + 2);

            if (first)
                *first = ((entry[0] & 0xc0) << 8) | (entry[0] & 0x3f);
            if (second)
                *second = entry[1];
            if (third)
                *third = read_le16_0800ACA8(entry + 2);
            if (fourth)
                *fourth = read_le16_0800ACA8(entry + 4);
        } else {
            const u8 *entry = table->data + (index * 8 + 2);

            if (first)
                *first = read_le16_0800ACA8(entry);
            if (second)
                *second = read_le16_0800ACA8(entry + 2);
            if (third)
                *third = read_le16_0800ACA8(entry + 4);
            if (fourth)
                *fourth = read_le16_0800ACA8(entry + 6);
        }
    } else {
        if (table->flags & 0x8000) {
            const u8 *entry = table->data + (index * 2 + 2);

            if (first)
                *first = ((entry[0] & 0xc0) << 8) | (entry[0] & 0x3f);
            if (second)
                *second = entry[1];
        } else {
            const u8 *entry = table->data + (index * 4 + 2);

            if (first)
                *first = read_le16_0800ACA8(entry);
            if (second)
                *second = read_le16_0800ACA8(entry + 2);
        }
        if (third)
            *third = 0;
        if (fourth)
            *fourth = 0;
    }
}
