typedef signed short s16;
int CombineBattleOperands(s16 first, s16 second) asm("CoreRegion_0012FE28");
/* Signed16 inputs; arithmetic halving precedes the signed16 wrapped result. */
int CombineBattleOperands(s16 first, s16 second)
{
    return (s16)(first - (second >> 1));
}
