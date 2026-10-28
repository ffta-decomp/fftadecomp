/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
struct InventoryRecord { u16 item_id; u8 owned_count; u8 reserved_count; };
typedef char InventoryRecordSize[sizeof(struct InventoryRecord) == 4 ? 1 : -1];
extern struct InventoryRecord *GetInventoryPartition(u16, s32 *);
extern u8 GetInventoryItemClass(u16);
extern const u8 gInventoryClassForCategory[] __asm__("0x08393aca");


s32 CollectEligibleInventoryClassEntries(struct InventoryRecord **output, u8 category_index);
s32 CollectEligibleInventoryClassEntries(struct InventoryRecord **output, u8 category_index)
{
    s32 entry_count;
    struct InventoryRecord *entry;
    s32 selected_count;
    s32 entry_index;
    struct InventoryRecord **output_cursor;
    u8 item_class = gInventoryClassForCategory[category_index];

    if (item_class != 5)
        entry = GetInventoryPartition(1, &entry_count);
    else
        entry = GetInventoryPartition(362, &entry_count);
    selected_count = 0;
    entry_index = 0;
    if (entry_index < entry_count) {
        output_cursor = output;
        do {
        u16 item_id = entry->item_id;
        /* The four exclusions are observed policy; their shared role is unknown. */
        if (item_id == 51 || item_id == 148 || item_id == 286 || item_id == 302)
            goto next_entry;
        if (GetInventoryItemClass(item_id) == item_class && entry->owned_count != 0) {
            if (output == 0)
                return 1;
            *output_cursor++ = entry;
            selected_count++;
        }
next_entry:
        entry_index++;
        entry++;
        } while (entry_index < entry_count);
    }
    return selected_count;
}
