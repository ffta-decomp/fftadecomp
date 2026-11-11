#include "ffta/unsigned_types.h"
typedef struct {void *actor;void *target;u8 unknown08[4];u16 selector;} EffectContext;
u32 InitialGate(EffectContext*) __asm__("EffectRuleCall_08130DCC");
u32 UnitStateGate(void*) __asm__("UnitStateE9HasBit0");
u32 UnitProperty(void*,u32) __asm__("RetailCall_080c7ea4");
typedef char CheckSelector[(u32)&((EffectContext*)0)->selector==12?1:-1];
