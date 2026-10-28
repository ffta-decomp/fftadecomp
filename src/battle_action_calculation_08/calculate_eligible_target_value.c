/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u32 GetUnitProperty(const void *unit, u32 property);
extern u8 UnitPredicate_0012C960(const void *unit);
extern u32 EffectDirect_0012D2F0(const void *actor, const void *target, u32 value);

/* Declaration-only original call targets. */
asm(".global UnitPredicate_0012C960\n.thumb_set UnitPredicate_0012C960,0x0812c961\n.global EffectDirect_0012D2F0\n.thumb_set EffectDirect_0012D2F0,0x0812d2f1");
u32 CalculateEligibleTargetValue(const void *actor, const void *target, u32 value)
{
    GetUnitProperty(target, 22);
    if (UnitPredicate_0012C960(target))
        return 0;
    return EffectDirect_0012D2F0(actor, target, value);
}
