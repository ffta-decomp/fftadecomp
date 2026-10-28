/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitValue { u8 unknown00[24]; u16 value; };
struct EffectContext { void *actor; struct UnitValue *target; };
extern u32 UnitValueSuppression(const void *);
asm(".global UnitValueSuppression\n.thumb_set UnitValueSuppression,0x080cda4d");

s32 GetUnsuppressedRoundedHalfValue(struct EffectContext *effect)
{
    u32 value;
    s32 amount;
    if((u8)UnitValueSuppression(effect->target)) return 0;
    value=effect->target->value;
    amount=value-(value>>1);
    if(amount<=0) amount=1;
    return amount;
}
