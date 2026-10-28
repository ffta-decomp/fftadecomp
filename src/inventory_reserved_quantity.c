typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct InventoryEntry {
    u16 item;
    u8 quantity;
    u8 reserved_quantity;
};

extern struct InventoryEntry gInventoryEntries[];

static inline struct InventoryEntry *GetInventoryPartition(u16 item, int *count)
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

/* Byte 3 is bounded by the quantity; its gameplay role remains unassigned. */
void AdjustInventoryReservedQuantity(u16 item, u8 increase)
{
    struct InventoryEntry *entry;
    int entry_count;
    int index;

    if (!item)
        return;
    entry = GetInventoryPartition(item, &entry_count);
    for (index = 0; index < entry_count; ++index, ++entry) {
        if (entry->item == item)
            break;
    }
    if (index == entry_count)
        return;
    if (increase) {
        if (entry->reserved_quantity >= entry->quantity)
            return;
        entry->reserved_quantity++;
    } else {
        if (!entry->reserved_quantity)
            return;
        entry->reserved_quantity--;
    }
}

asm(".align 2, 0");
