#include "interfaces_round04.h"

u32 EvaluateBattleEffectResolutionRate(void)
{
    void *target;
    u32 category, reaction, rate;
    volatile EffectRuleContext *context = (volatile EffectRuleContext *)0x0200f3f0;
    EffectCallback callback;
    EffectCallback volatile *rate_callbacks;
    volatile EffectRuleContext *dispatch_context;
    if (!(u8)ResolutionInitialGate(context->actor, context->target,
                                  EffectByte(context->descriptor, 1))) return 0;
    if (EffectByte(context->descriptor, 1) == 74 && !ResolutionCode74Gate(context->target)) return 0;
    if (!(u8)ResolutionCompatibilityGate(context->target,
                                         EffectByte(context->descriptor, 1))) return 0;
    if (context->item == 0) category = 17;
    else category = EffectItemProperty(context->item, 3);
    if (ResolutionAbilityProperty(context->action, 3) == 1 && category - 13 <= 1) goto reaction_gate;
    /* The second property read is required even when the first returned 1. */
    if (ResolutionAbilityProperty(context->action, 3) != 3) goto dispatch_gate;
    reaction_gate:
    reaction = (u16)ResolutionReaction(context->target);
    target = context->target;
    if ((u8)ResolutionPointGate(target, (s8)EffectByte(target, 246),
                                (s8)EffectByte(target, 247)) && reaction == 6 && ResolutionAbilityProperty(context->action, 17) == 0) return 0;
    dispatch_gate:
    if (EffectByte(context->descriptor, 1) == 7 && EffectHalf(context->target, 214) == 0) return 0;
    rate_callbacks = BattleEffectRateCallbacks;
    dispatch_context = (volatile EffectRuleContext *)0x0200f3f0;
    callback = rate_callbacks[EffectByte(dispatch_context->descriptor, 2)];
    rate = (u8)EffectCallThroughR1(dispatch_context, callback);
    if (rate != 0 && (u8)ResolutionForce100Gate(context->target)) rate = 100;
    return rate;
}
