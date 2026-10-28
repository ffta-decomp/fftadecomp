/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
struct UnitHealth { u8 prefix[24]; u16 current; u16 maximum; };
struct StateSlot { u32 occupied; u8 gap[12]; };
extern const struct StateSlot gStateSlots[];
extern u8 UnitField27HasBit14(const void *unit);
extern u8 UnitPredicate_000C8260(const void *unit);
extern u8 UnitPredicate_0012C960(const void *unit);
extern s32 DivideSigned(s32 numerator, s32 denominator);

asm(".global gStateSlots\n.set gStateSlots,0x02002e78\n.global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9\n.global UnitPredicate_000C8260\n.thumb_set UnitPredicate_000C8260,0x080c8261\n.global UnitPredicate_0012C960\n.thumb_set UnitPredicate_0012C960,0x0812c961\n.global DivideSigned\n.thumb_set DivideSigned,0x081426b9");
static inline u8 HasFreeStateSlot(const struct StateSlot *slots)
{
    int index;
    for (index = 0; index <= 19; index++) {
        if (!slots[index].occupied)
            return 1;
    }
    return 0;
}
s32 EvaluateHealthStateSlotRule(const struct UnitHealth *unit, u16 parameter)
{
    const struct StateSlot *slots = gStateSlots;
    if (UnitField27HasBit14(unit) || UnitPredicate_000C8260(unit) || UnitPredicate_0012C960(unit) || parameter <= 1)
        return 0;
    if (!HasFreeStateSlot(slots))
        return 0;
    return DivideSigned((unit->maximum - unit->current) * 100, unit->maximum) >> 2;
}
