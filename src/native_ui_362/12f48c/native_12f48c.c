#include "interfaces.h"

static inline int ClassifyAbility(u16 ability_id)
{
    register int result asm("r0");
    if (ability_id == 0 || GetAbilityProperty(ability_id, 29) != 0)
        result=0;
    else
        result=1;
    asm("" : "+r"(result));
    return result;
}

/* Slot B selects an optional factor; property results stay full-width. */
s16 CoreContinuation_0012F48C(const u8 *unit, s16 input_value, u16 ability_id, u16 item_id)
{
    s32 value = input_value;
    int ability_class;
    ability_class = ClassifyAbility(ability_id);
    switch (ReadAbilitySlotBValue(unit)) {
    case 1:
        if (ability_class == 0)
            value = (s32)((u32)value * 307U) >> 8;
        break;
    case 3:
        if (ability_class == 1)
            value = (s32)((u32)value * 307U) >> 8;
        break;
    case 4:
        if (ability_id != 0 && GetAbilityProperty(ability_id, 2) != 0)
            value = (s32)((u32)value * 332U) >> 8;
        break;
    case 7:
        if (ability_id == 0 && item_id != 0 && GetItemProperty(item_id, 6) == 1)
            value = (s32)((u32)value * 307U) >> 8;
        break;
    }
    return value;
}
