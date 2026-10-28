#ifndef SCENE_MODE_INTERFACES_H
#define SCENE_MODE_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u8 before_identity[4]; u8 identity; u8 before_flags[35]; u16 flags; u8 tail[222]; } SceneUnit;
typedef struct { u8 before_units[128]; SceneUnit units[24]; u8 before_pending[0x3c24 - 0x1940]; u32 pending_operations; u8 before_mode_marker[3]; u8 mode_marker; u8 before_reference[2]; u16 reference_3c2e; u8 before_reference_3c9c[0x6c]; u16 reference_3c9c; u8 marker_3c9e; u8 marker_3c9f; } SceneSave;
typedef struct { u8 before_counters[0xa8]; u8 counter_a8; u8 counter_a9; u8 counter_aa; u8 before_reference[0x1bd6 - 0xab]; u16 reference_1bd6; } SceneContent;
typedef struct { u8 before_fields[0x94]; u16 field_94; u16 field_96; } SceneRuntime;
/* Callback addresses are stored here; their later execution ABI is not inferred. */
typedef void (*SceneContinuation)(void);
typedef void (*SceneClearRoutine)(void *destination, u32 byte_count);
extern SceneSave gSceneSave;
extern SceneContent gSceneContent;
extern SceneRuntime gSceneRuntime;
extern u8 gSceneUnitsToClear[3168];
extern u32 gSceneObjectCell;
extern u8 gSceneTaskGroup;
extern SceneClearRoutine const gSceneClearRoutine;
extern void WriteSceneSaveByte(u32 index, u32 value);
extern void SetSceneGameFlag(u16 flag, u32 value);
extern u32 ReadSceneGameFlag(u32 flag);
extern void RestorePreviousSceneMode(void);
extern void ResetSceneUnits(void);
extern void ClearSceneObject(u32 *cell);
extern void InitializeSceneObject(u32 *cell, u32 zero);
extern void EnsureSceneRuntimeObject(void);
extern void FinishSceneUnitReset(void);
extern void AttachSceneContinuation(void *group, u32 slot, SceneContinuation callback);
extern void SceneCoreCallback(void);
extern void BattleFrameCallback(void);
extern void SceneAuxiliaryCallback(void);
extern void SceneFinishCallback(void);
extern void UnitSelectionCallback(void);
extern void MissionSceneCallback(void);
extern void MissionSceneFinalCallback(void);
extern void BattleSceneCallback(void);
extern void BattleSceneFinalCallback(void);
extern void CollectionSceneCallback(void);
extern void SaveSceneCallback(void);
extern void GameControllerCallback(void);
extern void ScenePolicyCallback(void);
typedef char scene_unit_stride_is_264[(sizeof(SceneUnit)==264)?1:-1];
typedef char scene_units_end_is_1940[((u32)&((SceneSave*)0)->before_pending==0x1940)?1:-1];
typedef char pending_offset_is_3c24[((u32)&((SceneSave*)0)->pending_operations==0x3c24)?1:-1];
typedef char reference_offset_is_3c9c[((u32)&((SceneSave*)0)->reference_3c9c==0x3c9c)?1:-1];
asm(
    ".global WriteSceneSaveByte\n.thumb_set WriteSceneSaveByte,0x080c95c1\n"
    ".global SetSceneGameFlag\n.thumb_set SetSceneGameFlag,0x080c9575\n"
    ".global ReadSceneGameFlag\n.thumb_set ReadSceneGameFlag,0x080c9541\n"
    ".global RestorePreviousSceneMode\n.thumb_set RestorePreviousSceneMode,0x08123d51\n"
    ".global ResetSceneUnits\n.thumb_set ResetSceneUnits,0x08096ba1\n"
    ".global ClearSceneObject\n.thumb_set ClearSceneObject,0x08024759\n"
    ".global InitializeSceneObject\n.thumb_set InitializeSceneObject,0x08024abd\n"
    ".global EnsureSceneRuntimeObject\n.thumb_set EnsureSceneRuntimeObject,0x08121bf5\n"
    ".global FinishSceneUnitReset\n.thumb_set FinishSceneUnitReset,0x0802dba1\n"
    ".global AttachSceneContinuation\n.thumb_set AttachSceneContinuation,0x08006add\n"
    ".global SceneCoreCallback\n.thumb_set SceneCoreCallback,0x080231e9\n"
    ".global BattleFrameCallback\n.thumb_set BattleFrameCallback,0x08096e79\n"
    ".global SceneAuxiliaryCallback\n.thumb_set SceneAuxiliaryCallback,0x080d36b1\n"
    ".global SceneFinishCallback\n.thumb_set SceneFinishCallback,0x080231f5\n"
    ".global UnitSelectionCallback\n.thumb_set UnitSelectionCallback,0x0802326d\n"
    ".global MissionSceneCallback\n.thumb_set MissionSceneCallback,0x080615e1\n"
    ".global MissionSceneFinalCallback\n.thumb_set MissionSceneFinalCallback,0x08064ef9\n"
    ".global BattleSceneCallback\n.thumb_set BattleSceneCallback,0x0805cf5d\n"
    ".global BattleSceneFinalCallback\n.thumb_set BattleSceneFinalCallback,0x0805d0e1\n"
    ".global CollectionSceneCallback\n.thumb_set CollectionSceneCallback,0x0805873d\n"
    ".global SaveSceneCallback\n.thumb_set SaveSceneCallback,0x08068ae1\n"
    ".global GameControllerCallback\n.thumb_set GameControllerCallback,0x080543ed\n"
    ".global ScenePolicyCallback\n.thumb_set ScenePolicyCallback,0x08050f1d\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
    ".global gSceneSave\n.set gSceneSave,0x02000000\n"
    ".global gSceneContent\n.set gSceneContent,0x020020d0\n"
    ".global gSceneRuntime\n.set gSceneRuntime,0x0200f390\n"
    ".global gSceneUnitsToClear\n.set gSceneUnitsToClear,0x02002fc4\n"
    ".global gSceneObjectCell\n.set gSceneObjectCell,0x0200f3ac\n"
    ".global gSceneTaskGroup\n.set gSceneTaskGroup,0x03002710\n"
    ".global gSceneClearRoutine\n.set gSceneClearRoutine,0x0836d4b8\n"
);
#endif
