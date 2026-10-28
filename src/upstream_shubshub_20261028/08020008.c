/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020008.c
 * Original SHA-256: a7a39fdf23eb6475a1accafb4745122abb6cef87976112c8434a920218771b47
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08020008..0x0802006C: 100 bytes. */
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

u8 func_08020008(void)
{
    const u8 *base = data_08569104;
    ResourceSelection *selection = &data_02007F10;
    const ResourceRecord *record = &((const ResourceRecord *)base)[selection->selected];
    if (has_resource(record)) {
        const Resource *resource = (const Resource *)(base + record->resource_offset);
        if (selection->position + 1 < resource->count)
            return 1;
    }
    return 0;
}
