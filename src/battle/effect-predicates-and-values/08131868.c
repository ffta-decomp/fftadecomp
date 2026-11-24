/* Method-local interface declarations from the frozen build. */
#include "ffta/unsigned_types.h"
typedef signed int s32;
struct UnitValues { u8 unknown00[24]; u16 current; u16 maximum; };
struct EffectContext { struct UnitValues *actor; void *target; };
extern u32 UnitValueSuppression(const void *);
asm(".global UnitValueSuppression\n.thumb_set UnitValueSuppression,0x080cda4d");

s32 GetUnsuppressedMissingActorValue(struct EffectContext *effect)
{
    s32 amount;
    if((u8)UnitValueSuppression(effect->target)) return 0;
    amount=effect->actor->maximum-effect->actor->current;
    if(amount<=1) amount=0;
    return amount;
}
