typedef signed int s32;
extern s32 QueryPairRate(void *, void *, unsigned int, unsigned int);
asm(".global QueryPairRate\n.thumb_set QueryPairRate,0x0812c8dd");

/* Preserve the sentinel/high rates; halve the signed ordinary-rate result. */
s32 ReadHalfEffectPairRate(void *actor, void *target)
{
    s32 rate = QueryPairRate(actor, target, 2, 0);
    if (rate <= 99)
        rate >>= 1;
    return rate;
}
