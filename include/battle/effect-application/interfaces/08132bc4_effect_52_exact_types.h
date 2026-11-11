#include "ffta/unsigned_types.h"
typedef signed int s32;
typedef struct {void *actor;void *target;void *affected;u8 unknown12[26];u16 flags;} EffectContext;
void ApplyKind(EffectContext*,u32) __asm__("EffectApplicationCall_08131DD4");
void SetState(void*,u32) __asm__("SetUnitStateEABit5");
u32 ReadCounter(void*) __asm__("ReadUnitCounterDA");
void WriteCounter(void*,u32) __asm__("WriteUnitCounterDA");
typedef char CheckFlags[(u32)&((EffectContext*)0)->flags==38?1:-1];
