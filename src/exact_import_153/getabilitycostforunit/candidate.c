#include "contract.h"

s32 GetAbilityCostForUnit(const u8 *unit, u16 ability_id)
{
    u16 cost;
    if (ability_id == 0)
        return 0;
    cost = GetAbilityProperty(ability_id, 2);
    switch ((u8)GetUnitCostModifier(unit)) {
    case 4:
        cost *= 2;
        break;
    case 10:
    {
        s32 signed_cost = (s16)cost;
        if (signed_cost & 1)
            cost = signed_cost + 1;
        cost = (s16)cost >> 1;
        break;
    }
    }
    return (s16)cost;
}
