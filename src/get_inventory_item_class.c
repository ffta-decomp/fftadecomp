typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetItemProperty(u16 item_id, u8 selector);
extern u8 IsItemIdInRange1To252(u16 item_id);
/* Classify an item through observed property selectors and ID ranges. */
u8 GetInventoryItemClass(u16 item_id)
{
    if (GetItemProperty(item_id, 6) == 3) return 0;
    if (GetItemProperty(item_id, 6) == 4) return 1;
    if (IsItemIdInRange1To252(item_id)) return 2;
    if (GetItemProperty(item_id, 3) == 20) return 3;
    if (GetItemProperty(item_id, 3) == 29 || GetItemProperty(item_id, 6) == 5 || GetItemProperty(item_id, 3) == 28) return 4;
    if ((u16)(item_id - 362) <= 13) return 5;
    return 255;
}
