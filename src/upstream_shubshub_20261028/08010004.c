/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010004.c
 * Original SHA-256: 89b1d65fa33573d069f5f16fffbaa5752f63556a1fa7bf407c82a163336cd45f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08010004..08010056: 82 bytes. */
struct Entry {
    u16 first;
    u16 second;
};

struct EntryBuffer {
    u8 unknown_00[8];
    struct Entry entries[160];
};

extern struct EntryBuffer *func_0800C614(void *object);
extern void func_0800C64C(void *object);

void func_08010004(void *object, s16 start, u8 count,
                   const struct Entry *source)
{
    struct EntryBuffer *buffer = func_0800C614(object);
    s32 position = start;
    s32 i;

    for (i = 0; i < count; i++, position++) {
        if (position < 0)
            continue;
        if (position >= 160)
            break;
        buffer->entries[position].first = source[i].first;
        buffer->entries[position].second = source[i].second;
    }
    func_0800C64C(object);
}
