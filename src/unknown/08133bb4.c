typedef unsigned char u8;
extern void ClearUnitStatesFromDetailMask(int detail_index, u8 *unit)
    __asm__("EffectApplicationCall_08131C28");
/* This battle-facing entry reverses the established helper's argument order. */
void ClearBattleUnitStatesFromDetail(u8 *unit, int detail_index)
{
    ClearUnitStatesFromDetailMask(detail_index, unit);
}
