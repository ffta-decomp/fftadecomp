typedef unsigned char u8;

extern u8 EvaluateBattleCounterD8Condition(const u8 *unit);

/* Returns the observed condition selecting counter +0xd8 value three. */
u8 UseThreeForBattleCounterD8(const u8 *unit)
{
    return EvaluateBattleCounterD8Condition(unit);
}
