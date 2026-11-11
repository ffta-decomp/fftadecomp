#include "abi/interfaces/0813091c_bindings.h"

u32 ReadEffectSignedQuarterAmount(volatile EffectRuleContext *context)
{
    return context->amount >> 2;
}
