/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800AEA0.c
 * Original SHA-256: 3ad190ff7cc48374c1b30b81f91b991cc4d00a84dde48ab2e116f9270c7ddbc5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Table0800AEA0 {
    u16 unknown_00;
    u16 flags;
    u16 unknown_04;
    u16 current;
    u16 unknown_08[2];
    u16 end;
    u8 unknown_0e[10];
    const u8 *data;
};

static inline u16 read_le16_0800AEA0(const u8 *data)
{
    u32 low = data[0];

    return (data[1] << 8) | low;
}

/* 0x0800AEA0..0x0800AF04: 100 bytes. */
u16 func_0800AEA0(const struct Table0800AEA0 *table)
{
    u16 count = table->current;

    if (table->flags & 0x40) {
        count = table->end - count;
        if (table->flags & 8) {
            if (!(table->flags & 0x8000)) {
                const u8 *entry = table->data;

                entry += table->end * 8;

                if (read_le16_0800AEA0(entry + 4) == 999)
                    count--;
            }
        } else {
            if (!(table->flags & 0x8000)) {
                const u8 *entry = table->data;

                entry += table->end * 4;

                if (read_le16_0800AEA0(entry + 4) == 999)
                    count--;
            }
        }
    }
    return count;
}
