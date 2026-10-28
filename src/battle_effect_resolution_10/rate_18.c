#include "interfaces.h"

u32 ReadEffectEquipmentDependentRate(volatile EffectRuleContext *context)
{
    u16 equipment[2];
    if (!ResolutionEquipmentOutput(context->target, equipment)) return 0;
    return (u8)ResolutionBaseRate(context);
}
