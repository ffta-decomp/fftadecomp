/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct EffectContext { void *actor; void *target; };
extern u32 TargetExclusionPredicate(const void *);
extern u32 UnitModePredicate(const void *);
extern u32 TargetFinalExclusion(const void *);
asm(".global TargetExclusionPredicate\n.thumb_set TargetExclusionPredicate,0x080c8281\n.global UnitModePredicate\n.thumb_set UnitModePredicate,0x080c8241\n.global TargetFinalExclusion\n.thumb_set TargetFinalExclusion,0x080c8385");

u32 EffectTargetHasDifferentUnitMode(struct EffectContext *effect)
{
    u8 actor_mode;
    if((u8)TargetExclusionPredicate(effect->target)) return 0;
    actor_mode=UnitModePredicate(effect->actor);
    if((u8)UnitModePredicate(effect->target)==actor_mode) return 0;
    if((u8)TargetFinalExclusion(effect->target)) return 0;
    return 1;
}
