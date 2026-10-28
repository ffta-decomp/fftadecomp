typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct InventoryRecord { u16 item_id; u8 owned_count; u8 reserved_count; };
extern struct InventoryRecord gInventoryEntries[];
static inline struct InventoryRecord *InventoryForItem(u16 item, int *count)
{
    struct InventoryRecord *entries = gInventoryEntries;
    u32 size = 361;
    if (item > size && item <= 375) {
        entries = &gInventoryEntries[361];
        size = 14;
    }
    if (count) *count = size;
    return entries;
}
u8 HasInventoryItem(u16 item)
{
    struct InventoryRecord *entry;
    int count;
    int i;
    if (!item) return 0;
    entry = InventoryForItem(item, &count);
    for (i = 0; i < count; i++, entry++) {
        if (entry->item_id == item && entry->owned_count) return 1;
    }
    return 0;
}
