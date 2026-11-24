#ifndef EFFECT_STATUS_EXEMPTIONS_H
#define EFFECT_STATUS_EXEMPTIONS_H
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u32 UnitHasSaveGatedStatusPair(void *unit);
extern u32 PassesActorTargetStatusPolicy(void *actor, void *target);
extern u32 ReadEffectCategory(u32 effect_id);
__asm__(".global UnitHasSaveGatedStatusPair\n.thumb_set UnitHasSaveGatedStatusPair, 0x08130835");
__asm__(".global PassesActorTargetStatusPolicy\n.thumb_set PassesActorTargetStatusPolicy, 0x08130869");
__asm__(".global ReadEffectCategory\n.thumb_set ReadEffectCategory, 0x08133971");
#endif
