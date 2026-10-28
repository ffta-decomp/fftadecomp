#ifndef RECOVERED_SCENE_ENTITY_ABI_H
#define RECOVERED_SCENE_ENTITY_ABI_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
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
void FilterSceneEntitiesForTransition_08124850(u32);
#endif
