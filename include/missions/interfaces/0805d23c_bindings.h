typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
extern u8 *gMissionContext;extern u8 gMissionData[];extern void (*gClearRoutine)(void*,u32);
extern void NResetPair(u8,u8),NInitializePolicy(u8);extern u32 NResolveSelector(u32),NCollectScene(void*,u32,u8),NCollectPending(void*,u32,u8),NCollectAvailable(void*,u32);extern u8 NHasAvailable(void);
#define AT(o) (gMissionContext+(o))
#define BYTE(o) (*(u8*)AT(o))
asm(".global gMissionContext\n.set gMissionContext,0x0200f448");
asm(".global gMissionData\n.set gMissionData,0x02000000");
asm(".global gClearRoutine\n.set gClearRoutine,0x0836d4b8");
asm(".global NResetPair\n.thumb_set NResetPair,0x08060ded");
asm(".global NInitializePolicy\n.thumb_set NInitializePolicy,0x080cfcd1");
asm(".global NResolveSelector\n.thumb_set NResolveSelector,0x08036351");
asm(".global NCollectScene\n.thumb_set NCollectScene,0x080d1b81");
asm(".global NCollectPending\n.thumb_set NCollectPending,0x080d0591");
asm(".global NCollectAvailable\n.thumb_set NCollectAvailable,0x080d0ab1");
asm(".global NHasAvailable\n.thumb_set NHasAvailable,0x0805d1a5");
