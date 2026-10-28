/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08146FB8.c
 * Original SHA-256: fbc5c0cd51221f1d2c8908b7c7651cf1f0324880dc5fa8c3b4e0be07bb2e764a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08146FB8..0x08147068: 176 bytes, 80 instructions. */
typedef struct {
    u16 current;
    u16 target;
    u16 first;
    u16 second;
    u8 unknown_08[8];
    u8 active;
    u8 unknown_11[7];
} RangeData;

typedef struct Interval {
    u16 kind;
    u16 setting;
    u16 flags;
    u16 first;
    u16 last;
    u8 unknown_0a[2];
    RangeData range;
    struct Interval *previous;
    struct Interval *next;
} Interval;

typedef struct {
    void *allocator;
    Interval *head;
} IntervalList;

typedef void (*BufferInitializer)(void *, u32);
extern IntervalList data_03003C60;
extern BufferInitializer g_callbacks_0836D4B8[];
extern void func_08146DC8(u16 first, u16 last, u16 flags);
extern void *func_08007138(void *allocator, u32 size);
extern void *func_0814873C(Interval *entry);

static inline Interval *allocate_interval(void)
{
    IntervalList *list = &data_03003C60;
    Interval *entry = func_08007138(list->allocator, sizeof(*entry));
    Interval *tail;

    g_callbacks_0836D4B8[0](entry, sizeof(*entry));
    if (list->head == 0) {
        list->head = entry;
        entry->previous = 0;
        entry->next = 0;
    } else {
        tail = list->head;
        while (tail->next != 0)
            tail = tail->next;
        tail->next = entry;
        entry->previous = tail;
        entry->next = 0;
    }
    return entry;
}

static inline void initialize_range(RangeData *range, u16 amount, u16 value)
{
    range->current = range->target = amount;
    range->first = range->second = value;
    range->active = 1;
}

void *func_08146FB8(u16 first, u16 last, u16 amount, u16 setting,
                    u16 value)
{
    Interval *entry;

    func_08146DC8(first, last, 30);
    entry = allocate_interval();
    if (entry == 0)
        return 0;
    if (amount == 0)
        amount = 1;
    initialize_range(&entry->range, amount, value);
    entry->first = first;
    entry->last = last;
    entry->setting = setting;
    entry->flags = 2;
    entry->kind = 1;
    return func_0814873C(entry);
}
