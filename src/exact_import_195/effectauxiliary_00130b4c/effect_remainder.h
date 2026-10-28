#ifndef CONVERGE198_REMAINDER_H
#define CONVERGE198_REMAINDER_H
typedef unsigned char u8;
typedef unsigned int u32;
struct EffectUnit { u8 unknown_00[9]; u8 field_09; };
struct EffectPair { struct EffectUnit *actor, *target; };
extern u32 UnitField19IsZero(struct EffectUnit *) __asm__("0x080c8280");
extern u32 UnsignedEffectRemainder(u32, u32) __asm__("0x08142b28");
u32 TestEffectTargetRemainderThreeZero(struct EffectPair *);
#endif
