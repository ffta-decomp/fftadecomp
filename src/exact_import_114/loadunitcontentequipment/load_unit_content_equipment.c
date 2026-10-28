#include "unit_model_c01.h"

extern u32 AdjustInventoryReservedQuantity(u16 item_id, u32 quantity);
typedef void (*EquipmentCopy)(u8 *, const u8 *, u32);

void LoadUnitContentEquipment(u8 *unit, const u8 *content)
{
    u32 eligible = 1;
    u16 *item_slot;
    s32 remaining_slots;

    /* The retail copy entry is loaded from an initialized IWRAM dispatch slot. */
    (*(EquipmentCopy const *)0x0836d4bc)(unit + 0x2a, content + 8, 10);
    if ((u8)UnitField27HasBit15(unit) != 0 ||
        (u8)UnitField27HasBit13(unit) != 0)
        eligible = 0;
    if (ReadUnitField(unit, 3) == 23 &&
        (u8)UnitField01Equals(unit, 94) == 0)
        eligible = 0;

    item_slot = (u16 *)(unit + 0x2a);
    remaining_slots = 4;
    do {
        if (eligible) {
            UnitModelExternalCall_CA900(*item_slot, 1);
            AdjustInventoryReservedQuantity(*item_slot, 1);
        }
        UnitModelExternalCall_CCF44(unit, *item_slot);
        ++item_slot;
    } while (--remaining_slots >= 0);
}
