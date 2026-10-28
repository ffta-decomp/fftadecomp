/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020628.c
 * Original SHA-256: 8c738e9f5ac8ea2ec5d249fa999451b91b9170cb23d24c2a3ca59ca0e52fcbf7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 resource_offset;
    u8 unknown_54[4];
} ResourceRecord08020628;

typedef struct {
    u16 selected;
} ResourceSelection08020628;

extern const u8 data_08569104[];
extern ResourceSelection08020628 data_02007F10;

u8 func_08020628(void)
{
    const u8 *base = data_08569104;
    ResourceSelection08020628 *selection = &data_02007F10;
    const ResourceRecord08020628 *record =
        &((const ResourceRecord08020628 *)base)[selection->selected];

    return record->resource_offset != 0;
}
