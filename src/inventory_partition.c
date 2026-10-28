typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct InventoryRecord { u16 item_id; u8 owned_count; u8 reserved_count; };
extern struct InventoryRecord gInventoryEntries[];
/* Select the primary or extended inventory partition and optionally report its size. */
struct InventoryRecord *GetInventoryPartition(u16 item, int *count)
{
    struct InventoryRecord *entries = gInventoryEntries;
    u32 size = 361;
    if (item > size && item <= 375) {
        entries = &gInventoryEntries[361];
        size = 14;
    }
    if (count)
        *count = size;
    return entries;
}
