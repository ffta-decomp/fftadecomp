#include "unit_model_c01.h"

u32 GetUnitEquippedStat24(const u8 *unit, u32 include_equipment_raw)
{
    u8 include_equipment = (u8)include_equipment_raw;
    u16 base_value = *(const u16 *)(unit + 0x24);
    s32 signed_base_value;

    if (include_equipment != 0) {
        u32 equipment_total = 0;
        const u16 *equipment_slot = (const u16 *)(unit + 0x2a);
        s32 slots_remaining = 4;
        do {
            u16 item_id = *equipment_slot;
            if (item_id != 0)
                equipment_total += GetItemProperty(item_id, 12);
            equipment_slot++;
        } while (--slots_remaining >= 0);

        signed_base_value = (s16)base_value;
        base_value = (u16)(signed_base_value + equipment_total);
    }

    {
        s32 result = (s16)base_value;
        return (u32)(result > 999 ? 999 : result);
    }
}
