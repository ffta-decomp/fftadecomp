typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 GetUnitProperty(const u8 *unit, u8 selector);
extern u32 GetItemProperty(u16 item_id, u8 selector);
extern const u32 gEquipmentClassMasks[];

/* Test the item category bit against the observed unit class equipment mask. */
u8 UnitItemCategoryAllowed(const u8 *unit, u16 item_id)
{
    u32 class_mask = gEquipmentClassMasks[GetUnitProperty(unit, 36)];
    u8 item_category = GetItemProperty(item_id, 3);
    return (class_mask & (1u << (item_category - 1))) != 0;
}
