typedef unsigned char u8;
typedef signed int s32;

extern s32 CalculateUnitSpeed(const u8 *unit);
extern u8 UnitStateECBit2(const u8 *unit);
extern u8 UnitStateEAHasBit1(const u8 *unit);
extern u8 UnitStateEAHasBit5(const u8 *unit);
extern u8 UnitStateEAHasBit6(const u8 *unit);

/* Applies the observed speed-halving and speed-doubling status modifiers. */
s32 GetEffectiveUnitSpeed(const u8 *unit)
{
    s32 speed = CalculateUnitSpeed(unit);

    if (UnitStateECBit2(unit) || UnitStateEAHasBit1(unit))
        speed >>= 1;
    if (UnitStateEAHasBit5(unit))
        speed <<= 1;
    if (UnitStateEAHasBit6(unit))
        speed >>= 1;
    return speed;
}
