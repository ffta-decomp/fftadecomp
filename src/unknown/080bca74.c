/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080BCA74.c
 * Original SHA-256: 073fc7d83d693f3f079c3e16acae45053208b6c90d586b5cccfe750c0f872724
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct PoolEntry PoolEntry;
struct PoolEntry {
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s8 priority;
    u8 active;
    u8 unknown_12[2];
    PoolEntry *previous;
    PoolEntry *next;
};

typedef struct {
    PoolEntry entries[16];
    PoolEntry *head;
    u16 cursor;
    s16 delay;
} EntryPool;

static inline s32 findFree(PoolEntry *entry, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++, entry++) {
        if (entry->active == 0 && entry->next == 0 && entry->previous == 0)
            return i;
    }
    return -1;
}

PoolEntry *func_080BCA74(EntryPool *pool)
{
    s16 offset;
    PoolEntry *entry;

    offset = findFree(&pool->entries[pool->cursor], 16 - pool->cursor);
    if (offset >= 0) {
        pool->cursor += offset;
    } else {
        offset = findFree(pool->entries, 16);
        if (offset < 0)
            return 0;
        pool->cursor = offset;
    }
    entry = &pool->entries[pool->cursor];
    pool->cursor++;
    if (pool->cursor > 15)
        pool->cursor = 0;
    return entry;
}
