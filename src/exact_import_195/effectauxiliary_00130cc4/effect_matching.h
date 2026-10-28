#ifndef CONVERGE196_EFFECT_MATCHING_H
#define CONVERGE196_EFFECT_MATCHING_H
typedef unsigned char u8;
typedef unsigned int u32;
struct EffectPair { void *actor; void *target; };
extern u32 UnitStatusBit15(void *) __asm__("0x080c8240");
extern u32 UnitField19IsZero(void *) __asm__("0x080c8280");
u32 TestEffectMatchingProperty(struct EffectPair *) __asm__("TestEffectMatchingProperty");
#endif
