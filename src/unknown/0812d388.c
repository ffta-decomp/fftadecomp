typedef unsigned int u32;
extern u32 QueryPairRate(void *actor, void *target, u32 mode, u32 option);
asm(".global QueryPairRate\n.thumb_set QueryPairRate,0x0812c8dd");

u32 ReadEffectPairQueryD388(void *actor, void *target)
{
    return QueryPairRate(actor, target, 2, 0);
}
