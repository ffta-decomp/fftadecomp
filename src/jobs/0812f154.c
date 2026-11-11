/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct UnitBattleState;
extern int UnitField19IsZero(const struct UnitBattleState *unit);
extern u8 UnitStateE8HasBit5(const struct UnitBattleState *unit);
__asm__(".global UnitField19IsZero\n.thumb_set UnitField19IsZero, 0x080c8281");
__asm__(".global UnitStateE8HasBit5\n.thumb_set UnitStateE8HasBit5, 0x080cd915");

u32 HasUnitStateE8Bit5WithField19Set(const struct UnitBattleState *unit);
u32 HasUnitStateE8Bit5WithField19Set(const struct UnitBattleState *unit)
{
    if ((u8)UnitField19IsZero(unit))
        return 0;
    if (UnitStateE8HasBit5(unit))
        return 1;
    return 0;
}
