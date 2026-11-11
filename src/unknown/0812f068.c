typedef signed int s32;
typedef unsigned int u32;
extern s32 QueryPairRate(void *, void *, unsigned int, unsigned int);
asm(".global QueryPairRate\n.thumb_set QueryPairRate,0x0812c8dd");

/* Compare the signed result only after the original wrapping word shift. */
s32 ReadDoubleEffectPairRate(void *actor, void *target)
{
    s32 rate = QueryPairRate(actor, target, 2, 0);
    rate = (s32)((u32)rate << 1);
    if (rate > 100)
        rate = 100;
    return rate;
}
