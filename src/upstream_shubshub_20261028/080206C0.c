/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080206C0.c
 * Original SHA-256: 0b5e13137f4d855e97aab73228a8369ddbca899ee76c2b4d48514d55c13e044c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080206C0..0x08020712: 82 bytes / 37 instructions. */
struct __attribute__((packed)) ResourceRecord080206C0 {
    u8 unknown_00[0x50];
    u32 resource_offset;
    u8 unknown_54[4];
};

struct Selection080206C0 {
    u16 selected;
    u8 unknown_02[0x26];
    u8 position;
};

extern const u8 data_08569104[];
extern struct Selection080206C0 data_02007F10;

static inline u8 has_resource(const struct ResourceRecord080206C0 *record)
{
    return record->resource_offset != 0;
}

u8 func_080206C0(void)
{
    const u8 *base = data_08569104;
    struct Selection080206C0 *selection = &data_02007F10;
    const struct ResourceRecord080206C0 *record =
        &((const struct ResourceRecord080206C0 *)base)[selection->selected];

    if (has_resource(record) == 0)
        return 0;
    return selection->position;
}
