#include "interfaces.h"
u32 ApplyEffectWhenHealthIsCritical(UnitHealthView *unit, void *other)
    __asm__("EffectDirect_0012DAB8");

u32 ApplyEffectWhenHealthIsCritical(UnitHealthView *unit, void *other)
{
    u32 maximum_health_tenth = DivideUnsigned(unit->maximum_health, 10);
    u32 current_health = unit->current_health;
    if (current_health >= (u16)maximum_health_tenth || current_health > 9)
        return 0;
    return ApplyEffectMode(unit, other, 2, 0);
}
