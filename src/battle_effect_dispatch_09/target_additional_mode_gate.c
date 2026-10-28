/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectContext { u32 unknown00; void *target; u8 unknown08[30]; u16 flags; };
extern u32 TargetExclusionPredicate(const void *);
extern u32 TargetModePredicate(const void *);
asm(".global TargetExclusionPredicate\n.thumb_set TargetExclusionPredicate,0x080c8281\n.global TargetModePredicate\n.thumb_set TargetModePredicate,0x080c8241");

extern u32 TargetAdditionalExclusion(const void *);
asm(".global TargetAdditionalExclusion\n.thumb_set TargetAdditionalExclusion,0x081308f5");

u32 EffectTargetPassesAdditionalModeGate(struct EffectContext *effect)
{
    u8 target_mode;
    if((u8)TargetExclusionPredicate(effect->target)) return 0;
    if((u8)TargetAdditionalExclusion(effect->target)) return 0;
    target_mode=TargetModePredicate(effect->target);
    if(effect->flags&128) {
        if(!target_mode) return 0;
    } else {
        if(target_mode) return 0;
    }
    return 1;
}
