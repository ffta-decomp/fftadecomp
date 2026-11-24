#ifndef SCENE_ROSTER_CLEANUP_H
#define SCENE_ROSTER_CLEANUP_H
typedef unsigned char u8;
typedef unsigned int u32;
struct SceneSaveBlock { u8 unknown0[0x3c24]; u32 pending_operations; };
extern void *gSceneRestoreChild;
extern u8 gSceneRestoreBuffer[],gSceneRestoreVram[];
extern const u8 gSceneRestoreResource[];
extern struct SceneSaveBlock gSceneSaveBlock;
extern void DestroySceneRestoreChild(void **child);
extern void ReleaseCurrentSceneState(void);
extern void RefreshSceneRestoreResources(void);
extern void DecodeSceneRestoreResource(void *destination,const void *source);
extern void CpuFastSetSceneRestore(const void *source,void *destination,u32 control);
extern u32 ReadSceneRestoreFlag(u32 flag);
extern void UpdateCurrentContentFlag(u32 enabled);
extern void RefreshSceneRestoreDisplay(void);
extern void CompactSavedUnitRoster(void);
extern void EnsureSceneRestoreActor(void);
__asm__(".global gSceneRestoreChild\n.set gSceneRestoreChild,0x0200f3ac\n.global gSceneRestoreBuffer\n.set gSceneRestoreBuffer,0x02003cb0\n.global gSceneRestoreVram\n.set gSceneRestoreVram,0x06012500\n.global gSceneRestoreResource\n.set gSceneRestoreResource,0x083bbc7c\n.global gSceneSaveBlock\n.set gSceneSaveBlock,0x02000000\n.global DestroySceneRestoreChild\n.thumb_set DestroySceneRestoreChild,0x080247fd\n.global ReleaseCurrentSceneState\n.thumb_set ReleaseCurrentSceneState,0x08096cb9\n.global RefreshSceneRestoreResources\n.thumb_set RefreshSceneRestoreResources,0x08022dd1\n.global DecodeSceneRestoreResource\n.thumb_set DecodeSceneRestoreResource,0x0800543d\n.global CpuFastSetSceneRestore\n.thumb_set CpuFastSetSceneRestore,0x08141869\n.global ReadSceneRestoreFlag\n.thumb_set ReadSceneRestoreFlag,0x080c9541\n.global UpdateCurrentContentFlag\n.thumb_set UpdateCurrentContentFlag,0x08096de5\n.global RefreshSceneRestoreDisplay\n.thumb_set RefreshSceneRestoreDisplay,0x08022a9d\n.global CompactSavedUnitRoster\n.thumb_set CompactSavedUnitRoster,0x080891bd\n.global EnsureSceneRestoreActor\n.thumb_set EnsureSceneRestoreActor,0x08121bf5");
#endif
