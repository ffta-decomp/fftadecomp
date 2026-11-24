/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u8 UnitStateE9HasBit2(const void *unit);
extern u8 UnitStateEBHasBit4(const void *unit);

__asm__(".global UnitStateE9HasBit2\n.thumb_set UnitStateE9HasBit2, 0x080cd98d");

/* Add the three source-ordered unit-state contributions; score meaning is unproved. */
s32 DeriveStatePairAdjustment(const void *first_unit, const void *second_unit)
{
    s32 adjustment = 0;
    if ((u8)UnitStateE9HasBit2(second_unit) != 0)
        adjustment -= 20;
    if ((u8)UnitStateEBHasBit4(second_unit) != 0)
        adjustment -= 10;
    if ((u8)UnitStateE9HasBit2(first_unit) != 0)
        adjustment += 50;
    return adjustment;
}
