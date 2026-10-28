typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectResponseContext { void *actor; void *target; u8 unknown_08[4]; u16 action; u8 unknown_0E[24]; u16 flags; };
u32 CalculateUnitEffectResponse(void *actor, void *target, u32 action, u32 mode) __asm__("RetailCall_08130150");
asm(".global RetailCall_08130150\n.thumb_set RetailCall_08130150,0x08130151\n");
