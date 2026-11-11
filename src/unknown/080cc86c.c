typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
struct InventoryRecord { u16 item_id; u8 owned_count; u8 reserved_count; };
extern struct InventoryRecord *GetInventoryPartition(u16 item_id, s32 *count);
/* Return an owned item record index within its selected inventory partition. */
u16 FindInventoryItemIndex(u16 item_id)
{
    s32 count;
    struct InventoryRecord *entries = GetInventoryPartition(item_id, &count);
    u16 index = 0;
    for (; index < count; ++index) {
        if (entries[index].item_id == item_id && entries[index].owned_count)
            return index;
    }
    return 65535;
}
