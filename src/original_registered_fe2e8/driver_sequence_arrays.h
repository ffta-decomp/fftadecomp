#ifndef FFTA_FE2E8_DRIVER_SEQUENCE_ARRAYS_H
#define FFTA_FE2E8_DRIVER_SEQUENCE_ARRAYS_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef struct ActorModel ActorModel;
typedef struct TargetRecord {
    u8 unknown[14];
    u16 kind;
} TargetRecord;
/* Native OUT objects are three contiguous halfwords, not an 8-byte ARM struct. */
typedef u16 WorldPosition3[3];
typedef s16 TilePosition3[3];
typedef struct EventRecord {
    u16 state, unknown_02;
    void *source;
    u8 unknown_08[12];
    u16 selector, mode;
    u32 unknown_18;
} EventRecord;
typedef struct DriverEvent {
    u16 state, unknown_02;
    WorldPosition3 *from, *to;
    u32 unknown_0c, unknown_10;
    u16 selector;
    s16 direction;
    u32 unknown_18;
} DriverEvent;
typedef void (*TaskCallback)(TaskNode *, EventRecord *, void *);
typedef struct DriverWork {
    u8 unknown_00[20];
    u16 parameter20;
    u8 unknown_16[130];
    void *actor;
    u8 unknown_9c[376];
    void *channel;
} DriverWork;
typedef struct SequenceWork {
    u8 unknown_00[5];
    u8 mode, ready, special;
    u8 unknown_08[4];
    WorldPosition3 from;
    u16 unknown_12;
    WorldPosition3 to;
    u16 unknown_1a;
    ActorModel *model;
    void *target;
    void *source;
    TaskNode *driver, *followup;
    void *special_child;
    TaskNode *initial_child, *ready_child, *secondary_child;
} SequenceWork;
typedef char WorldPosition3Is6[sizeof(WorldPosition3) == 6 ? 1 : -1];
typedef char TilePosition3Is6[sizeof(TilePosition3) == 6 ? 1 : -1];
typedef char EventRecordIs28[sizeof(EventRecord) == 28 ? 1 : -1];
typedef char DriverEventIs28[sizeof(DriverEvent) == 28 ? 1 : -1];
typedef char DriverWorkIs536[sizeof(DriverWork) == 536 ? 1 : -1];
typedef char SequenceWorkIs64[sizeof(SequenceWork) == 64 ? 1 : -1];

extern TaskNode *CreateInitialSequence(void *, const void *, u32, u32, u32, TaskNode *);
extern void AdvanceCurrentSequenceState(void);
extern TaskNode *PollInitialSequence(TaskNode *);
extern u32 ReadSourceUnavailable(void *);
extern ActorModel *ResolveSourceModel(void *);
extern TaskNode *CreateReadySequence(ActorModel *, u8 *, u8, u8, u8, u8, u16, TaskNode *);
extern void ReadModelPosition(ActorModel *, u16 *, u16 *, u16 *);
extern u32 CountSequenceTargets(void *);
extern void *ReadTargetModel(void *, u32);
extern void ReadTargetPosition(void *, u16 *, u16 *, u16 *);
extern void ReadFallbackPosition(void *, u16 *, u16 *, u16 *);
extern s32 ReadActorSignedDirection(ActorModel *);
extern u32 ReadSourceSelector(void *);
extern TaskNode *CreateOppositePhaseTask(TaskCallback, u16, const void *, TaskNode *);
extern void DriverSequenceCallback(TaskNode *, EventRecord *, void *);
extern u32 ReadTaskState(TaskNode *);
extern TargetRecord *ReadSequenceTarget(void *, u32);
extern DriverWork *ReadDriverWork(TaskNode *);
extern void ReadModelPhysicalPosition(ActorModel *, s16 *, s16 *, s16 *);
extern void *CreateSpecialTargetSequence(TargetRecord *, u16, u8, u8, u8, u32, TaskNode *);
extern void SetActorSequenceState(ActorModel *, u32);
extern void SetTaskState(TaskNode *, u32);
extern void StopDriverChannel(void *);
extern void ConfigureDriverActor(void *, u32);
extern void ApplySourceTargetStage(void *, void *);
extern TaskNode *CreateSecondarySequence(const void *, u32, u32, u32, TaskNode *);
extern TaskNode *PollSequenceTask(TaskNode *);
extern void TargetFollowupCallback(TaskNode *, EventRecord *, void *);
extern void ApplySourceStage(void *, u32);
extern u32 IsActorSequenceFinished(ActorModel *);
extern void *PollSpecialTargetSequence(void *);
extern const u8 InitialSequenceData[];
extern const u8 SecondarySequenceData[];
#endif
