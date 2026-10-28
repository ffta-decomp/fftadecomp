#include "interfaces.h"

u32 ReadEffectSignedQuarterAmount(volatile EffectRuleContext *context)
{
    return context->amount >> 2;
}
