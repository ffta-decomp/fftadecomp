#ifndef FFTA_FDAB0_SEQUENCE_H
#define FFTA_FDAB0_SEQUENCE_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef struct EventRecord {
    u16 state, unknown_02;
    void *source;
    u32 parameter, unknown_0c, unknown_10;
    u16 selector, mode;
    u32 unknown_18;
} EventRecord;
typedef struct ContinuationWork {
    u16 unknown_00;
    u8 mode, status;
    u32 unknown_04;
    TaskNode *continuation, *followup;
    void *source;
    TaskNode *initial;
    u32 unknown_18;
} ContinuationWork;
typedef u32 (*TaskCallback)(TaskNode *, EventRecord *, void *);
typedef char EventIs28[sizeof(EventRecord)==28 ? 1 : -1];
typedef char WorkIs28[sizeof(ContinuationWork)==28 ? 1 : -1];
extern TaskNode *CreateInitialSequence(void *, const void *, u32, u32, u32, TaskNode *);
extern void AdvanceCurrentSequenceState(void);
extern TaskNode *PollInitialSequence(TaskNode *);
/* Fourth full-word parameter is forwarded unchanged by the accepted helper;
 * this call site supplies the actual work+3 address. */
extern TaskNode *CreateRecordEffectContinuation(void *, u8, u8, u32, TaskNode *);
extern TaskNode *CreateOppositePhaseTask(TaskCallback, u16, const EventRecord *, TaskNode *);
extern TaskNode *PollContinuation(TaskNode *);
extern TaskNode *PollFollowup(TaskNode *);
extern u32 FollowupCallback(TaskNode *, EventRecord *, void *);
extern const u8 InitialSequenceData[];
#endif
