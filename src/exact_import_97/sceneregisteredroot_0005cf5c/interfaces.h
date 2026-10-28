#ifndef MISSION_SELECTION_CONTROLLER_H
#define MISSION_SELECTION_CONTROLLER_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionLabel {
    const void *definition;
    u16 width, height;
    u8 unknown8[8];
};
struct MissionSelectionContext {
    u8 unknown0[0x119d];
    u8 message;
    u8 unknown119e[4];
    u8 continuation;
    u8 unknown11a3[0x147c - 0x11a3];
    struct MissionLabel title, subtitle;
    u8 unknown149c[0x14b4 - 0x149c];
};
struct MissionSaveView { u8 unknown0[0x219e]; u16 active_mission; };
extern struct MissionSelectionContext *gMissionSelection;
extern struct MissionSaveView gMissionSave;
extern u8 gSceneActive;
extern u8 gRuntimeInterface[];
extern const u8 gMissionTitle[], gMissionSubtitle[];
extern void (*gMissionClear)(void *,u32);
extern void *AllocateMissionContext(u32);
extern void FreeMissionContext(void *);
extern void ConfigureMissionRuntime(void *,u32,u32,u32,u32,u32);
extern void InitializeMissionLabel(struct MissionLabel *,const void *,u16,u16);
extern void SetupMissionContext(struct MissionSelectionContext *);
extern u32 StepMissionSelection(void);
extern u32 StepMissionDetails(void);
extern u32 StepMissionTransaction(void);
extern u32 StepMissionConfirmation(void);
extern u32 PollMissionContinuation(void);
extern u32 StepMissionCommit(void);
extern void DispatchMissionContinuation(u32);
extern void CommitMissionContinuation(void);
extern void TickMissionInterface(void);
typedef char MissionContextSize[sizeof(struct MissionSelectionContext)==0x14b4?1:-1];
typedef char MissionTitleOffset[((u32)&((struct MissionSelectionContext *)0)->title==0x147c)?1:-1];
__asm__(".global gMissionSelection\n.set gMissionSelection,0x0200f448\n.global gMissionSave\n.set gMissionSave,0x02000000\n.global gSceneActive\n.set gSceneActive,0x0200f390\n.global gRuntimeInterface\n.set gRuntimeInterface,0x030008b0\n.global gMissionTitle\n.set gMissionTitle,0x0851ba72\n.global gMissionSubtitle\n.set gMissionSubtitle,0x0851ba7a\n.global gMissionClear\n.set gMissionClear,0x0836d4b8\n.global AllocateMissionContext\n.thumb_set AllocateMissionContext,0x08022841\n.global FreeMissionContext\n.thumb_set FreeMissionContext,0x08022855\n.global ConfigureMissionRuntime\n.thumb_set ConfigureMissionRuntime,0x08029e49\n.global InitializeMissionLabel\n.thumb_set InitializeMissionLabel,0x08017fa9\n.global SetupMissionContext\n.thumb_set SetupMissionContext,0x0805f589\n.global StepMissionSelection\n.thumb_set StepMissionSelection,0x0805d535\n.global StepMissionDetails\n.thumb_set StepMissionDetails,0x0805d785\n.global StepMissionTransaction\n.thumb_set StepMissionTransaction,0x0805eaa9\n.global StepMissionConfirmation\n.thumb_set StepMissionConfirmation,0x0805efed\n.global PollMissionContinuation\n.thumb_set PollMissionContinuation,0x0805f2a9\n.global StepMissionCommit\n.thumb_set StepMissionCommit,0x0805f331\n.global DispatchMissionContinuation\n.thumb_set DispatchMissionContinuation,0x08009afd\n.global CommitMissionContinuation\n.thumb_set CommitMissionContinuation,0x08009fd1\n.global TickMissionInterface\n.thumb_set TickMissionInterface,0x08011c61\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
#endif
