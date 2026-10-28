typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectOperandContext { void *actor; void *target; u8 unknown_08[4]; u16 action; u16 item; u8 unknown_10[22]; u16 flags; };
u32 CalculateUnitEffectOperand(void *actor, void *target, u32 action, u32 item, u32 mode) __asm__("RetailCall_0813054c");
asm(".global RetailCall_0813054c\n.thumb_set RetailCall_0813054c,0x0813054d\n");
