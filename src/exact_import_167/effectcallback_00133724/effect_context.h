#ifndef EFFECT_CONTEXT_H
#define EFFECT_CONTEXT_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef struct EffectUnit {
    u8 unknown_00[0xD6];
    u16 counter_d6;
} EffectUnit;
typedef struct EffectContext {
    EffectUnit *actor;
    EffectUnit *target;
    u8 unknown_08[0x1E];
    u16 flags;
} EffectContext;
/* The existing global-context value dispatcher ignores incoming r0. */
extern s32 RetailCall_08131b20(void);
#endif
