typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct InventoryRecord {
    u16 item_id;
    u8 owned_count;
    u8 reserved_count;
};

extern struct InventoryRecord gInventoryEntries[];

/* IDs 362-375 use the 14-record extension after the 361 primary records.
 * Keep the capacity output: the retail inlined selector writes it on the
 * stack before the inventory scan. */
static inline struct InventoryRecord *SelectInventoryRecords(u16 item_id,
                                                             int *capacity)
{
    struct InventoryRecord *records = gInventoryEntries;
    u32 count = 361;

    if (item_id > count && item_id <= 375) {
        records = &gInventoryEntries[361];
        count = 14;
    }
    if (capacity != 0)
        *capacity = count;
    return records;
}

/* Return the owned-minus-reserved quantity with the original byte wrap. */
u8 GetInventoryAvailableQuantity(u16 item_id)
{
    struct InventoryRecord *record;
    int capacity;
    int index;

    if (item_id == 0)
        return 0;
    record = SelectInventoryRecords(item_id, &capacity);
    for (index = 0; index < capacity; ++index, ++record) {
        if (record->item_id == item_id)
            return record->owned_count - record->reserved_count;
    }
    return 0;
}
