typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

struct InventoryRecord {
    u16 item_id;
    u8 owned_count;
    u8 reserved_count;
};

extern struct InventoryRecord *GetInventoryPartition(u16 item_id, s32 *count);
extern u8 IsItemIdInRange1To252(u16 item_id);

/* Return whether any standard inventory record has a nonzero owned count. */
u8 HasOwnedStandardInventoryItem(void)
{
    struct InventoryRecord *entries;
    s32 count;
    s32 i;

    entries = GetInventoryPartition(0, &count);
    for (i = 0; i < count; i++, entries++) {
        if (IsItemIdInRange1To252(entries->item_id) && entries->owned_count != 0)
            return 1;
    }
    return 0;
}
