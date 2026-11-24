/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { void *unit; } BattleActor;
typedef struct { u8 count; u8 filters; } ActorCountFilter;
extern u32 UnitField19IsZero(const void *);
extern u32 UnitStateE8HasBit2(const void *);
extern u32 UnitStateE8HasBit6(const void *);
extern u32 UnitStateEDBit6(const void *);
extern u32 UnitField27HasBit13(const void *);
extern u32 TestUnitC84C0(const void *);
__asm__(".global TestUnitC84C0\n.thumb_set TestUnitC84C0,0x080c84c1\n");

/* Count an actor passing the observed unit gates and caller-specified filters. */
u32 CountFilteredActor(BattleActor *actor, ActorCountFilter *output)
{
    if ((u8)UnitField19IsZero(actor->unit) != 0 &&
        (u8)UnitStateE8HasBit2(actor->unit) == 0)
        return 1;
    if ((u8)UnitStateE8HasBit6(actor->unit) != 0)
        return 1;
    if ((u8)UnitStateEDBit6(actor->unit) != 0)
        return 1;
    if ((output->filters & 1) != 0 &&
        (u8)UnitField27HasBit13(actor->unit) != 0)
        return 1;
    if ((output->filters & 2) != 0 &&
        (u8)TestUnitC84C0(actor->unit) == 0)
        return 1;
    output->count++;
    return 1;
}
