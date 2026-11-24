typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

struct InventoryRecord {
    u16 item_id;
    u8 owned_count;
    u8 reserved_count;
};

extern struct InventoryRecord *GetInventoryPartition(u16 item_id, s32 *count);
extern u8 GetInventoryItemClass(u16 item_id);

/* Copy owned records in the requested observed item class into caller storage. */
u16 CopyInventoryClass(struct InventoryRecord *output, u8 category)
{
    s32 count;
    struct InventoryRecord *entries;
    u16 index;
    u16 written;

    if (category != 5)
        entries = GetInventoryPartition(1, &count);
    else
        entries = GetInventoryPartition(362, &count);
    index = 0;
    written = 0;
    while (index < count) {
        if (GetInventoryItemClass(entries[index].item_id) == category
            && entries[index].owned_count != 0) {
            output[written] = entries[index];
            ++written;
        }
        ++index;
    }
    return written;
}
