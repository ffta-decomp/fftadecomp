/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
struct InventoryRecord { u16 item_id; u8 owned_count; u8 reserved_count; };
typedef char InventoryRecordSize[sizeof(struct InventoryRecord) == 4 ? 1 : -1];
extern struct InventoryRecord *GetInventoryPartition(u16, s32 *);


u8 HasOwnedItemInEitherInventoryPartition(void);
u8 HasOwnedItemInEitherInventoryPartition(void)
{
    s32 count;
    struct InventoryRecord *entries;
    u16 entry_index;

    entries = GetInventoryPartition(1, &count);
    for (entry_index = 0; entry_index < count; entry_index++) {
        if (entries[entry_index].item_id != 0 && entries[entry_index].owned_count != 0)
            return 1;
    }
    entries = GetInventoryPartition(362, &count);
    for (entry_index = 0; entry_index < count; entry_index++) {
        if (entries[entry_index].item_id != 0 && entries[entry_index].owned_count != 0)
            return 1;
    }
    return 0;
}
