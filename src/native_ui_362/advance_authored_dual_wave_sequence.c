typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct NestedPositionRecord;
struct AuthoredWaveEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[14];
    u16 mode;
    u8 unknown18[4];
};
struct AuthoredWaveWork {
    u32 unknown00;
    u8 mode,complete;
    u16 unknown06;
    TaskNode *first,*second;
    struct NestedPositionRecord *record;
    void *actor;
    u32 unknown18;
    TaskNode *record_child,*sequence;
};
typedef char EventSize[(sizeof(struct AuthoredWaveEvent)==28)?1:-1];
typedef char WorkSize[(sizeof(struct AuthoredWaveWork)==36)?1:-1];
extern struct NestedPositionRecord *GetActorNestedRecord(void *);
extern void ProjectNestedRecord(const struct NestedPositionRecord *,u16 *,u16 *,u16 *);
extern u32 RequestSequencePosition(int,int);
extern void CleanupDefinitionInputs(void);
extern u32 QuerySequenceReadiness(void);
extern void SetNestedRecordCurrentValue(void *,u16);
extern TaskNode *CreateNestedRecordTask(void *,u8 *,u8,s8,u8,u8,u16,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *CreateOppositePhaseChild(TaskCallback,u16,const u32 *,TaskNode *);
extern TaskNode *PollAndReleaseChild(TaskNode *);
extern u32 PollNestedRecordHandles(void *);
extern s32 RunAuthoredDualWaveChild(TaskNode *,u16 *,void *);
extern s32 RunAuthoredFadeChild(TaskNode *,u16 *,void *);
extern const u8 gAuthoredWaveOpeningStage[];
extern const u8 gAuthoredWaveChildStage[];
__asm__(".global GetActorNestedRecord\n.thumb_set GetActorNestedRecord,0x080dd47d\n"
        ".global ProjectNestedRecord\n.thumb_set ProjectNestedRecord,0x080dbda1\n"
        ".global RequestSequencePosition\n.thumb_set RequestSequencePosition,0x080d8b29\n"
        ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
        ".global QuerySequenceReadiness\n.thumb_set QuerySequenceReadiness,0x080d8b4d\n"
        ".global SetNestedRecordCurrentValue\n.thumb_set SetNestedRecordCurrentValue,0x080de10d\n"
        ".global CreateNestedRecordTask\n.thumb_set CreateNestedRecordTask,0x080de4b1\n"
        ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
        ".global CreateOppositePhaseChild\n.thumb_set CreateOppositePhaseChild,0x08005b6d\n"
        ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x080e051d\n"
        ".global PollNestedRecordHandles\n.thumb_set PollNestedRecordHandles,0x080de1f1\n"
        ".global RunAuthoredDualWaveChild\n.thumb_set RunAuthoredDualWaveChild,0x081175d5\n"
        ".global RunAuthoredFadeChild\n.thumb_set RunAuthoredFadeChild,0x08117785\n"
        ".global gAuthoredWaveOpeningStage\n.set gAuthoredWaveOpeningStage,0x083a50dc\n"
        ".global gAuthoredWaveChildStage\n.set gAuthoredWaveChildStage,0x083a50e4");
s32 AdvanceAuthoredDualWaveSequence(TaskNode *,struct AuthoredWaveEvent *,struct AuthoredWaveWork *)
    __asm__("OriginalDualWaveSequence_00117884");
s32 AdvanceAuthoredDualWaveSequence(TaskNode *parent,struct AuthoredWaveEvent *event,
                                   struct AuthoredWaveWork *work)
{
    u16 x,y,depth;
    switch(event->phase) {
    case 0: {
        void *actor;
        work->mode=(u8)event->mode;
        actor=event->actor;
        work->actor=actor;
        work->record=GetActorNestedRecord(actor);
        ProjectNestedRecord(work->record,&x,&y,&depth);
        RequestSequencePosition((s16)(x-120),(s16)(y-96));
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256: {
        u8 readiness=(u8)QuerySequenceReadiness();
        if(readiness!=0) break;
        SetNestedRecordCurrentValue(work->record,60);
        work->record_child=CreateNestedRecordTask(work->record,&work->complete,
                                                  1,2,readiness,40,readiness,parent);
        work->sequence=CreateSequenceStage(gAuthoredWaveOpeningStage,1,4,0,parent);
        ++event->phase;
        break;
    }
    case 257: {
    /* Actual28B template. The existing constructor copies it, sets phase0,
     * and invokes children whose phase0 consumes no other template fields.
     * Preserve its opaque bytes; no zero initialization is introduced. */
    u32 child_event[7];
        if(work->complete==0) break;
        work->first=CreateOppositePhaseChild((TaskCallback)RunAuthoredDualWaveChild,
                                              48,child_event,parent);
        work->second=CreateOppositePhaseChild((TaskCallback)RunAuthoredFadeChild,
                                               36,child_event,parent);
        work->sequence=CreateSequenceStage(gAuthoredWaveChildStage,1,4,0,parent);
        ++event->phase;
        break;
    }
    case 258:
        work->first=PollAndReleaseChild(work->first);
        if(work->first!=0) break;
        work->second=PollAndReleaseChild(work->second);
        if(work->second!=0) break;
        if((u8)PollNestedRecordHandles(work->record)!=0)
            event->phase=2;
        break;
    }
    return 0;
}
