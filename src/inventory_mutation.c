/* Independently recovered from retail Thumb code at 0x080CA900. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct InventoryEntry {
    u16 item;
    u8 quantity;
    u8 reserved;
};

extern struct InventoryEntry gInventoryEntries[];

static inline struct InventoryEntry *InventoryPartitionForItem(u16 item, int *count)
{
    struct InventoryEntry *entries = gInventoryEntries;
    u32 entry_count = 361;

    if (item > entry_count && item <= 375) {
        entries = &gInventoryEntries[361];
        entry_count = 14;
    }
    if (count != 0)
        *count = entry_count;
    return entries;
}

int AddInventoryItem(u16 item, u8 quantity)
{
    struct InventoryEntry *entry;
    int entry_count;
    int index;
    u8 found = 0;

    if (!quantity || !item)
        return -1;

    entry = InventoryPartitionForItem(item, &entry_count);
    for (index = 0; index < entry_count; index++, entry++) {
        if (entry->item != 0 && entry->item == item) {
            found = 1;
            break;
        }
    }

    if (!found) {
        entry = InventoryPartitionForItem(item, &entry_count);
        for (index = 0; index < entry_count; index++, entry++) {
            if (entry->item == 0) {
                found = 1;
                break;
            }
        }
    }

    if (!found)
        return -1;

    if (!entry->item)
        entry->item = item;
    entry->quantity += quantity;
    if (entry->quantity > 99) {
        u8 uncapped_quantity = entry->quantity;
        entry->quantity = 99;
        return (signed char)(uncapped_quantity - 99);
    }
    return 0;
}

int RemoveInventoryItem(u16 item, u8 quantity)
{
    struct InventoryEntry *entry;
    int entry_count;
    int index;
    u8 found = 0;

    if (quantity) {
        if (!item)
            return -1;

        entry = InventoryPartitionForItem(item, &entry_count);
        for (index = 0; index < entry_count; index++, entry++) {
            if (entry->item != 0 && entry->item == item) {
                found = 1;
                break;
            }
        }

        if (!found)
            return -1;
        if (entry->quantity > quantity)
            entry->quantity -= quantity;
        else
            entry->quantity = 0;
    }
    return 0;
}
