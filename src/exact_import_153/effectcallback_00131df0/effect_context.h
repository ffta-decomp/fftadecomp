#ifndef EFFECT_CONTEXT_H
#define EFFECT_CONTEXT_H
typedef unsigned char u8;
typedef unsigned short u16;

/* Only the observed fields are named; field_d0 has no proved status caption. */
typedef struct EffectUnit {
    u8 unknown_00[0xD0];
    u16 field_d0;
} EffectUnit;
typedef struct EffectContext {
    u8 unknown_00[8];
    EffectUnit *unit;
    u8 unknown_0c[0x1A];
    u16 flags;
} EffectContext;
#endif
