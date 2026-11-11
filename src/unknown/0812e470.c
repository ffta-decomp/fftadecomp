typedef unsigned char u8;
typedef unsigned short u16;

extern u8 UseThreeForBattleCounterD8(const u8 *unit);
extern u8 ReadUnitCounterD8(const u8 *unit);
extern u8 UnitStateEDBit6(const u8 *unit);
extern u8 UnitStateE8HasBit6(const u8 *unit);
extern u8 UnitStateEAHasBit7(const u8 *unit);
extern u8 UnitStateEBHasBit2(const u8 *unit);
extern u8 UnitStateE9HasBit7(const u8 *unit);

/* Checks the counter and status gates shared by battle turn selection. */
u8 BattleUnitPassesTurnStateGate(const u8 *unit)
{
    if (UseThreeForBattleCounterD8(unit) && ReadUnitCounterD8(unit))
        return 0;
    if (UnitStateEDBit6(unit))
        return 0;
    if (*(const u16 *)(unit + 0x18) == 0)
        return 0;
    return 1;
}

/* Applies the additional state-byte exclusions used before turn processing. */
u8 CanBattleUnitTakeTurn(const u8 *unit)
{
    if (!BattleUnitPassesTurnStateGate(unit))
        return 0;
    if (UnitStateE8HasBit6(unit))
        return 0;
    if (UnitStateEAHasBit7(unit))
        return 0;
    if (UnitStateEBHasBit2(unit))
        return 0;
    if (UnitStateE9HasBit7(unit))
        return 0;
    return 1;
}
