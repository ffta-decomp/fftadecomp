/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800D73C.c
 * Original SHA-256: c6edffc75a5007801a143f71a494b6129d03522e64948f85dd21ec6a0a9d21ff
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 start;
    u8 end;
    u8 unknown_04[24];
} RangeEntry;

extern RangeEntry *func_0800C614(u32 handle);

static inline RangeEntry *get_range_entry(u32 handle, u8 kind, u8 index)
{
    RangeEntry *entry = 0;

    switch (kind) {
    case 0:
        entry = func_0800C614(handle);
        break;
    case 1:
        entry = &func_0800C614(handle)[index];
        break;
    case 2:
        entry = &func_0800C614(handle)[index];
        break;
    }
    return entry;
}

void func_0800D73C(u32 handle, u8 kind, u8 index, s16 start, s16 end)
{
    RangeEntry *entry = get_range_entry(handle, kind, index);

    if (start < 0)
        start = 0;
    else if (start >= 160)
        start = 160;
    if (end < 0)
        end = 0;
    else if (end >= 160)
        end = 159;
    entry->start = start;
    entry->end = end;
}
