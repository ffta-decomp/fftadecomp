typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {void *actor;void *target;u8 unknown08[30];u16 flags;u8 unknown40[8];u8 *descriptor;} EffectContext;
u32 Evaluate(void*,void*,u32) __asm__("EffectResolutionCall_0812F008");
u32 StateGate(void*) __asm__("EffectResolutionCall_080CD8FC");
typedef char CheckFlags[(u32)&((EffectContext*)0)->flags==38?1:-1];
typedef char CheckDescriptor[(u32)&((EffectContext*)0)->descriptor==48?1:-1];
