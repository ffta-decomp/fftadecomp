#include "interfaces.h"

void ApplyFourLinkedUnitStates(volatile ApplicationContext *context)
{
    EffectApplicationCall_08131DD4(context, 35);
    EffectApplicationCall_08131DD4(context, 37);
    EffectApplicationCall_08131DD4(context, 39);
    EffectApplicationCall_08131DD4(context, 41);
    if (context->flags & 16) return;
    SetUnitStateECBit3(context->affected, 1);
    SetUnitStateECBit5(context->affected, 1);
    SetUnitStateECBit7(context->affected, 1);
    SetUnitStateEDBit1(context->affected, 1);
}
