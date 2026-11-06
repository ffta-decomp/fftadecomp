#ifndef FFTA_FC800_APPROACH_SEQUENCE_H
#define FFTA_FC800_APPROACH_SEQUENCE_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef struct ActorRecord ActorRecord;
typedef struct EventRecord {
    u16 state, unknown_02;
    void *source;
    u8 unknown_08[12];
    u16 selector, mode;
    u32 unknown_18;
} EventRecord;
typedef struct DefinitionRamp {
    u16 value;
    s16 remaining, error;
    u16 step, period, magnitude;
} DefinitionRamp;
typedef struct ApproachWork {
    u16 x, y, timer;
    u8 mode, ready, direction, unknown_09[3];
    ActorRecord *source_actor, *projected_actor;
    void *source;
    TaskNode *initial;
    void *primary_resource;
    void *children[3];
    void *final_resource;
    TaskNode *palette_sequence;
    void *target_sequence;
    TaskNode *ready_sequence, *secondary;
    DefinitionRamp x_ramp, y_ramp;
} ApproachWork;
typedef char EventRecordIs28[sizeof(EventRecord) == 28 ? 1 : -1];
typedef char DefinitionRampIs12[sizeof(DefinitionRamp) == 12 ? 1 : -1];
typedef char ApproachWorkIs88[sizeof(ApproachWork) == 88 ? 1 : -1];
typedef char XRampAt64[(u32)&((ApproachWork *)0)->x_ramp == 64 ? 1 : -1];
typedef char YRampAt76[(u32)&((ApproachWork *)0)->y_ramp == 76 ? 1 : -1];
extern TaskNode *CreateInitialSequence(void *, const void *, u32, u32, u32, TaskNode *);
extern void AdvanceCurrentSequenceState(void);
extern TaskNode *PollInitialSequence(TaskNode *);
extern u32 ReadSourceUnavailable(void *);
extern TaskNode *CreateActorReadySequence(void *, ActorRecord **, u32, u32, u8 *, const void *, u32, u32, TaskNode *);
extern void ApplySourceTransition(void *, u32);
extern u32 QueryDefinitionReadiness(void);
extern u32 CheckSourceStage(void *, u32);
extern void *ReadSequenceTarget(void *, u32);
extern ActorRecord *ProjectActorWithDefaultTransition(void *, u16 *, u16 *, u16 *);
extern u32 ReadActorFlag15(ActorRecord *);
extern s32 ReadActorSignedDirection(ActorRecord *);
extern void *CreatePositionedResource(const void *, u32, s32, s32, u32, u32, u32, u32);
extern void ConfigureResourceOptionA(void *, u32);
extern void ConfigureResourceOptionB(void *, u32);
/* Parent call sites retain full SIGN16 coordinate values even where the
 * accepted helper subsequently consumes their low halfwords. */
extern void InitializeDefinitionRamp(DefinitionRamp *, s32, s32, u32);
extern void *CreateTargetSequence(void *, const void *, u32, u32, u32, TaskNode *, u32);
extern TaskNode *CreateSecondarySequence(const void *, u32, u32, u32, TaskNode *);
extern void CopyBytes(void *, const void *, u32);
extern void AdvanceDefinitionRamp(DefinitionRamp *);
extern void SetResourceCoordinates(void *, s32, s32, u32);
extern void CommitResource(void *);
extern u32 IsDefinitionRampComplete(DefinitionRamp *);
extern void RemoveDefinitionResource(void *);
extern TaskNode *CreateDefinitionPaletteTask(const void *, TaskNode *);
extern u32 IsActorSequenceFinished(ActorRecord *);
extern u32 PollAndReleaseDefinitionWorkset(void **, u32);
extern void *PollFinalResource(void *);
extern TaskNode *PollPaletteSequence(TaskNode *);
extern void *PollTargetSequence(void *);
extern const u8 InitialSequenceData[], ReadySequenceData[], TargetSequenceData[];
extern const u8 SecondarySequenceData[], ThresholdSource[];
extern const u8 PrimaryResourceData[], BurstResourceData[], FinalResourceData[];
extern const u8 PaletteSequenceData[];
#endif
