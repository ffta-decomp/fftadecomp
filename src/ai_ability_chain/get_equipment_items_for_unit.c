#include "retail_calls.h"

/* The helper initializes both halfwords before testing its eligibility gate. */
u32 GetEquipmentItemsForUnit(const u8 *unit, u16 *equipment_items)
{
    u32 item_count;
    s8 first_modifier;
    s8 second_modifier;

    equipment_items[0] = 0;
    equipment_items[1] = 0;

    /* Retail tests the helper's low byte; a nonzero upper word is ignored. */
    if ((u8)AiEquipmentHasAbilityGate(unit) != 0)
        return 0;

    item_count = AiFindAbilityEquipmentItems(unit, equipment_items);
    /* The ARM CMP/BLE sequence treats this full-width count as signed. */
    if ((s32)item_count <= 1)
        return item_count;

    first_modifier = (s8)(u8)AiGetItemProperty(equipment_items[0], 10);
    second_modifier = (s8)(u8)AiGetItemProperty(equipment_items[1], 10);
    if (first_modifier < second_modifier) {
        u16 first_item = equipment_items[0];
        equipment_items[0] = equipment_items[1];
        equipment_items[1] = first_item;
    }
    return item_count;
}
