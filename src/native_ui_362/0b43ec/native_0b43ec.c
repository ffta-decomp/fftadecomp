#include "interfaces.h"
static inline u32 ReadAbilityProperty16(u16 ability_id,u8 selector)
{
    u32 value=(u16)ReadAbilityProperty(ability_id,selector);
    asm("" : "+r"(value));
    return value;
}

/* Resolve the original action/item presentation code; code meanings remain provisional. */
u32 CoreFrontier_000B43EC(u16 ability_id, u16 item_id)
{
    s16 item_class;
    if (ability_id==0) {
        item_class=GetItemProperty(item_id,3);
        if ((u16)(item_class-13)<=1 || item_class==19)
            return 450;
        return 434;
    }
    if ((ReadAbilityProperty16(ability_id,4)&128)!=0)
        return 450;
    switch ((u16)ReadAbilityProperty(ability_id,6)) {
    case 2: return 4;
    case 3: return 68;
    case 4: return 35;
    case 5:
    case 6: return 50;
    case 7: return 19;
    default: return 66;
    }
}
