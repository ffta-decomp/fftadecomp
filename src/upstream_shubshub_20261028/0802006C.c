/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802006C.c
 * Original SHA-256: 7d574102be315e45653ad3d01ea35ba12a70712c9dd8970f54a09a3038681668
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0802006C..0x080200C6: 90 bytes. */
typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 resource_offset;
    u8 unknown_54[4];
} ResourceRecord;

typedef struct {
    u16 selected;
    u8 unknown_02[0x27];
    u8 position;
} ResourceSelection;

typedef struct {
    u8 unknown_00[0x0C];
    u8 count;
} Resource;

extern const u8 data_08569104[];
extern ResourceSelection data_02007F10;

static inline u8 has_resource(const ResourceRecord *record)
{
    return record->resource_offset != 0;
}

u8 func_0802006C(void)
{
    const u8 *base = data_08569104;
    ResourceSelection *selection = &data_02007F10;
    const ResourceRecord *record =
        &((const ResourceRecord *)base)[selection->selected];

    const Resource *resource;

    if (has_resource(record) == 0)
        return 0;
    resource = (const Resource *)(base + record->resource_offset);
    return resource->count - 1;
}
