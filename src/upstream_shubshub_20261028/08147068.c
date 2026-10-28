/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08147068.c
 * Original SHA-256: f8231d15fa72c568e05c7b613849087070c0fdf3a3739c0c97e1f95392c3644d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08147068..0x08147124: 188 bytes, 86 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 current;
    u16 target;
    u16 first;
    u16 second;
    const void *data;
    u16 count;
    u8 unknown_16[2];
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

static inline void initialize_range(RangeData *range, u16 amount, u16 value,
                                    const void *data)
{
    range->current = range->target = amount;
    range->first = range->second = value;
    range->data = data;
    range->count = 0;
}

void *func_08147068(u16 first, u16 last, u16 amount, u16 setting,
                    u16 value, const void *data)
{
    Interval *entry;

    func_08146DC8(first, last, 31);
    entry = allocate_interval();
    if (entry == 0)
        return 0;
    if (amount == 0)
        amount = 1;
    if (value == 0)
        value = 1;
    initialize_range(&entry->range, amount, value, data);
    entry->first = first;
    entry->last = last;
    entry->setting = setting;
    entry->flags = 4;
    entry->kind = 1;
    return func_0814873C(entry);
}
