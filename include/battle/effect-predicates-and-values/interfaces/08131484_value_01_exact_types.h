typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {void *actor;void *target;u8 unknown08[40];u8 *descriptor;} EffectContext;
u32 UnitProperty(void*,u32) __asm__("RetailCall_080c7ea4");
typedef char CheckDescriptor[(u32)&((EffectContext*)0)->descriptor==48?1:-1];
