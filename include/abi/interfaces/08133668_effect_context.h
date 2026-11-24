#ifndef EFFECT_CONTEXT_H
#define EFFECT_CONTEXT_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct EffectUnit EffectUnit;
typedef struct EffectContext {
    u8 unknown_00[8];
    EffectUnit *unit;
    u8 source_value;
    u8 unknown_0d[0x19];
    u16 flags;
} EffectContext;
extern void SetUnitStateEABit2(EffectUnit *unit, u8 enabled);
extern void WriteUnitCounterE6(EffectUnit *unit, u8 value);
#endif
