#ifndef RECOVERED_SCENE_ENTITY_ABI_H
#define RECOVERED_SCENE_ENTITY_ABI_H
#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed int s32;
#define WORD(p) (*(u32 *)(p))
#define HALF(p) (*(u16 *)(p))
#define BYTE(p) (*(u8 *)(p))
extern void *GetSceneActionContextBase(void);
extern u32 CountBattleUnitRecords(const void *,u32 *);
extern u32 EntityHelper_080C8240(void *);
extern u32 EntityHelper_080C8260(void *);
extern u32 EntityHelper_080C8298(void *);
extern u32 EntityHelper_080C8280(void *);
extern u32 EntityHelper_080CD92C(void *);
extern u32 EntityHelper_080CDADC(void *);
extern u32 EntityHelper_080CDA04(void *);
extern u32 EntityHelper_080CDB24(void *);
extern void ApplySceneEntityOperation_0809836C(void *,u32,s32,u32);
extern void ApplySceneEntityStateMasks(void *,u32,u32);
extern u32 UnsignedDivide(u32,u32);
extern void *EntityHelper_080C83CC(u32);
extern u8 *EntityHelper_08099560(void *,void *);
extern void EntityHelper_080CE380(void *,u32);
extern u8 *EntityHelper_08121CB4(u32);
extern u8 *EntityHelper_08121C58(u32);
extern u8 *EntityHelper_08121B64(u32);
extern void EntityHelper_08121B78(void *);
extern u32 EntityHelper_0801CC18(u32,u32);
extern void (*const gClearMemory)(void *,u32);
extern void (*gCopyRecordMemory)(void *,const void *,u32);
void UpdateSceneEntityActions_081247B4(u32);
void FilterSceneEntitiesForTransition_08124850(u8);
#endif

__asm__(".global GetSceneActionContextBase\n.thumb_set GetSceneActionContextBase,0x08096D7D");

__asm__(".global CountBattleUnitRecords\n.thumb_set CountBattleUnitRecords,0x08099CDD");

__asm__(".global UnsignedDivide\n.thumb_set UnsignedDivide,0x08142AB1");

__asm__(".global ApplySceneEntityStateMasks\n.thumb_set ApplySceneEntityStateMasks,0x0809A571");

__asm__(".global EntityHelper_080C8240\n.thumb_set EntityHelper_080C8240,0x080C8241");

__asm__(".global EntityHelper_080C8260\n.thumb_set EntityHelper_080C8260,0x080C8261");

__asm__(".global EntityHelper_080C8298\n.thumb_set EntityHelper_080C8298,0x080C8299");

__asm__(".global EntityHelper_080C8280\n.thumb_set EntityHelper_080C8280,0x080C8281");

__asm__(".global EntityHelper_080CD92C\n.thumb_set EntityHelper_080CD92C,0x080CD92D");

__asm__(".global EntityHelper_080CDADC\n.thumb_set EntityHelper_080CDADC,0x080CDADD");

__asm__(".global EntityHelper_080CDA04\n.thumb_set EntityHelper_080CDA04,0x080CDA05");

__asm__(".global EntityHelper_080CDB24\n.thumb_set EntityHelper_080CDB24,0x080CDB25");
