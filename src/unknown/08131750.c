typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
struct PreservedEffectValueView { u8 prefix[32]; s16 amount; };
typedef char amount_offset32[((u32)&(((struct PreservedEffectValueView *)0)->amount)==32)?1:-1];
/* Descriptor-bound signed value; this is the context itself, not its unit pointer. */
s32 ReadPreservedBattleEffectValue(const struct PreservedEffectValueView *context)
    asm("EffectAuxiliary_00131750");
s32 ReadPreservedBattleEffectValue(const struct PreservedEffectValueView *context)
{
    return context->amount;
}
