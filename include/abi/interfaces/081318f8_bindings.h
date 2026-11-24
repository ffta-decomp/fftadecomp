typedef unsigned int u32;
typedef int s32;
typedef signed short s16;
struct EffectRuleContext;
s32 CalculateEffectBase(struct EffectRuleContext *) __asm__("RetailCall_0813189c");
u32 NextEffectRandom(void) __asm__("RetailCall_08002804");
s32 DivideEffectSigned(s32 dividend, s32 divisor) __asm__("RetailCall_081426b8");
s32 RemainderEffectSigned(s32 dividend, s32 divisor) __asm__("RetailCall_08142950");
asm(".global RetailCall_0813189c\n.thumb_set RetailCall_0813189c,0x0813189d\n.global RetailCall_08002804\n.thumb_set RetailCall_08002804,0x08002805\n.global RetailCall_081426b8\n.thumb_set RetailCall_081426b8,0x081426b9\n.global RetailCall_08142950\n.thumb_set RetailCall_08142950,0x08142951\n");
