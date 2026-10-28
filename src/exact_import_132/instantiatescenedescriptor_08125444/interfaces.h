typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef unsigned int u32;
struct Unit {u8 unknown00[24];u16 value24,saved26,value28,saved30;u8 unknown20[8];u16 flags40;u8 unknown2A[222];};
struct Entity {u8 unknown00[31];u8 identity;u8 unknown20[8];u32 flags40;u8 unknown2C[4];u32 flags48;};
extern struct Unit *ResolveSceneUnitByEncodedId(u32);
extern struct Unit *FindUnitPoolRecordById(u32);
extern void *GetSceneActionContextBase(void);
extern struct Entity *FindSceneEntityForUnitRecord(void *,struct Unit *);
extern void PlacementHelper_0809A304(struct Entity *);
extern void PlacementHelper_08124710(struct Entity *,u8,u8);
#define ClearRange (*(void (**)(u8 *,int))0x0836d4b8)
struct SpawnDescriptor {u8 type,reference;u8 x[4],y[4];};
extern struct Entity *RetailCall_08099644(void *,signed char,signed char);
extern u32 DetermineSceneFacing_08124ACC(u8,u8,u8,u8);
extern struct Entity *PlacementHelper_081242A0(u8,u8,u8,u8,u8,u8,u8);
