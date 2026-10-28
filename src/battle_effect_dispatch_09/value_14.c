#include "interfaces.h"

u32 ReadEffectMaximumDelegate(volatile EffectRuleContext *context)
{
    return EffectMaximumRule(context);
}
