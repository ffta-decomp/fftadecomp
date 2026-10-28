/* MIXED: actual2B itemaddress ADD only; signedbase/property14/clamp logic remains C. */
#include "interfaces.h"

s32 CoreConsumer_000CA580(const struct UnitEquipmentValueView *unit)
{
    s16 base_value = unit->value_d2;
    s32 equipment_total = 0;
    s32 slot;
    for (slot = 0; slot < 5; slot++) {
        register u32 slot_byte_offset __asm__("r0") = slot * 2;
        register const u16 *first_item __asm__("r1") = unit->equipment;
        u16 item_id;
        __asm__ volatile(".Lw6_CA580_actual_item_address:\nadd %0,%0,%1"
            : "+r"(first_item) : "r"(slot_byte_offset) : "cc");
        item_id = *first_item;
        if (item_id != 0)
            equipment_total += GetItemProperty(item_id, 14);
    }
    base_value = (s16)base_value + equipment_total;
    if ((s16)base_value < 0)
        base_value = 0;
    return (s16)base_value;
}
