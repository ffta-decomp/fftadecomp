typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct RangeRequestNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct AuthoredSequenceEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[14];
    u16 variant;
    u8 unknown18[4];
};
struct AuthoredSequenceWork {
    u16 delay;
    u8 cursor,count,variant,complete;
    u16 unknown06;
    u32 unknown08;
    u16 *saved_values;
    TaskNode *first,*second,*third,*fourth;
    void *record,*target;
    TaskNode *palette;
    struct RangeRequestNode *range;
    u32 unknown30;
    void *actor;
    TaskNode *record_child,*motion_child;
    TaskNode *motions[4];
    TaskNode *stage;
};
typedef char EventSize[sizeof(struct AuthoredSequenceEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct AuthoredSequenceWork)==84?1:-1];
extern u32 ReadDefinitionTargetCount(void *);
extern void *GetDefinitionTargetComponent(void *,u8);
extern void RefreshDefinitionTarget(void *);
extern void CleanupDefinitionInputs(void);
extern void *GetActorNestedRecord(void *);
extern void SetNestedRecordCurrentValue(void *,u16);
extern TaskNode *CreateNestedRecordTask(void *,u8 *,u8,s8,u8,u8,u16,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *CreatePaletteTask(const void *,TaskNode *);
extern TaskNode *PollAndReleasePalette(TaskNode *);
extern TaskNode *CreateRecordMotionTask(u8,u32,void *,u16,u32,TaskNode *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
extern TaskNode *CreateOppositePhaseChild(TaskCallback,u16,const u32 *,TaskNode *);
extern TaskNode *PollAndReleaseChild(TaskNode *);
extern void SelectActorFlag256(void *,u8);
extern const u16 *GetDefinitionValues(void);
extern u16 *AllocateSequenceBuffer(u32);
extern void MapDefinitionValues(const u16 *,u16 *,u16,u8);
extern struct RangeRequestNode *BeginSavedRangeTransition(u32,u32,u32,const u16 *);
extern struct RangeRequestNode *ReleaseCompletedRangeRequest(struct RangeRequestNode *);
extern void FreeSequenceBuffer(void *);
extern void *GetDefinitionTarget(void *,u8);
extern void *ReadOptionalTargetObject(void *);
extern u32 SelectObjectViewport(void *);
extern u32 QuerySequenceReadiness(void);
extern u32 PollMotionArray(TaskNode **,u32);
extern TaskNode *CreateTargetMotion(void *,const void *,u8,u16,u32,TaskNode *,u32);
extern s32 RunFirstStageChild(TaskNode *,u16 *,void *);
extern s32 RunSecondStageChild(TaskNode *,u16 *,void *);
extern s32 RunThirdStageChild(TaskNode *,u16 *,void *);
extern s32 RunFourthStageChild(TaskNode *,u16 *,void *);
extern const u8 gAuthoredOpeningStage[],gAuthoredSecondStage[],gAuthoredPalette[];
extern const u8 gAuthoredTargetMotion[];
__asm__(".global ReadDefinitionTargetCount\n.thumb_set ReadDefinitionTargetCount,0x080dd495\n"
 ".global GetDefinitionTargetComponent\n.thumb_set GetDefinitionTargetComponent,0x080dd4b5\n"
 ".global RefreshDefinitionTarget\n.thumb_set RefreshDefinitionTarget,0x080de269\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
 ".global GetActorNestedRecord\n.thumb_set GetActorNestedRecord,0x080dd47d\n"
 ".global SetNestedRecordCurrentValue\n.thumb_set SetNestedRecordCurrentValue,0x080de10d\n"
 ".global CreateNestedRecordTask\n.thumb_set CreateNestedRecordTask,0x080de4b1\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
 ".global CreatePaletteTask\n.thumb_set CreatePaletteTask,0x080d4705\n"
 ".global PollAndReleasePalette\n.thumb_set PollAndReleasePalette,0x080d4775\n"
 ".global CreateRecordMotionTask\n.thumb_set CreateRecordMotionTask,0x080df9ad\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x080dba5d\n"
 ".global CreateOppositePhaseChild\n.thumb_set CreateOppositePhaseChild,0x08005b6d\n"
 ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x080e051d\n"
 ".global SelectActorFlag256\n.thumb_set SelectActorFlag256,0x080de3bd\n"
 ".global GetDefinitionValues\n.thumb_set GetDefinitionValues,0x080d3905\n"
 ".global AllocateSequenceBuffer\n.thumb_set AllocateSequenceBuffer,0x0800a655\n"
 ".global MapDefinitionValues\n.thumb_set MapDefinitionValues,0x08148319\n"
 ".global BeginSavedRangeTransition\n.thumb_set BeginSavedRangeTransition,0x08147d2d\n"
 ".global ReleaseCompletedRangeRequest\n.thumb_set ReleaseCompletedRangeRequest,0x081484cd\n"
 ".global FreeSequenceBuffer\n.thumb_set FreeSequenceBuffer,0x0800a669\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x080dd4a5\n"
 ".global ReadOptionalTargetObject\n.thumb_set ReadOptionalTargetObject,0x080dd4c5\n"
 ".global SelectObjectViewport\n.thumb_set SelectObjectViewport,0x080db839\n"
 ".global QuerySequenceReadiness\n.thumb_set QuerySequenceReadiness,0x080d8b4d\n"
 ".global PollMotionArray\n.thumb_set PollMotionArray,0x080dbab9\n"
 ".global CreateTargetMotion\n.thumb_set CreateTargetMotion,0x080dcfe5\n"
 ".global RunFirstStageChild\n.thumb_set RunFirstStageChild,0x08118a09\n"
 ".global RunSecondStageChild\n.thumb_set RunSecondStageChild,0x08118ac1\n"
 ".global RunThirdStageChild\n.thumb_set RunThirdStageChild,0x08118b95\n"
 ".global RunFourthStageChild\n.thumb_set RunFourthStageChild,0x08118c4d\n"
 ".global gAuthoredOpeningStage\n.set gAuthoredOpeningStage,0x083a624c\n"
 ".global gAuthoredSecondStage\n.set gAuthoredSecondStage,0x083a6254\n"
 ".global gAuthoredPalette\n.set gAuthoredPalette,0x0894c358\n"
 ".global gAuthoredTargetMotion\n.set gAuthoredTargetMotion,0x083a6238");
s32 AdvanceAuthoredFourStageTargetSequence(TaskNode *,struct AuthoredSequenceEvent *,struct AuthoredSequenceWork *)
    __asm__("OriginalActionCallback_00118D20");
s32 AdvanceAuthoredFourStageTargetSequence(TaskNode *parent,struct AuthoredSequenceEvent *event,
                                           struct AuthoredSequenceWork *work)
{
    /* Four actual independent 28B constructor templates at SP16/44/72/100. */
    u32 first_event[7],second_event[7],third_event[7],fourth_event[7];
    u16 phase=event->phase;
    switch(phase) {
    case 0: {
        void *actor;
        u32 count;
        u8 ordinal;
        work->variant=(u8)event->variant;
        actor=event->actor;
        work->actor=actor;
        count=ReadDefinitionTargetCount(actor);
        work->count=(u8)count;
        ordinal=0;
        if(phase<(u8)count) {
            do {
                RefreshDefinitionTarget(GetDefinitionTargetComponent(work->actor,ordinal));
                ++ordinal;
            } while(ordinal<work->count);
        }
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256:
        work->record=GetActorNestedRecord(work->actor);
        SetNestedRecordCurrentValue(work->record,60);
        work->record_child=CreateNestedRecordTask(work->record,&work->complete,
                                                  2,2,0,0,0,parent);
        work->stage=CreateSequenceStage(gAuthoredOpeningStage,1,4,0,parent);
        ++event->phase;
        break;
    case 257:
        if(work->complete==0) break;
        work->palette=CreatePaletteTask(gAuthoredPalette,parent);
        ++event->phase;
        break;
    case 258:
        work->palette=PollAndReleasePalette(work->palette);
        if(work->palette!=0) break;
        work->stage=CreateSequenceStage(gAuthoredSecondStage,1,4,0,parent);
        work->motion_child=CreateRecordMotionTask(5,0,work->record,16,6,parent);
        ++event->phase;
        break;
    case 259:
        work->motion_child=PollAndReleaseMotion(work->motion_child);
        if(work->motion_child!=0) break;
        first_event[1]=(u32)work->actor;
        work->first=CreateOppositePhaseChild((TaskCallback)RunFirstStageChild,16,first_event,parent);
        ++event->phase;
        break;
    case 260:
        work->first=PollAndReleaseChild(work->first);
        if(work->first!=0) break;
        second_event[1]=(u32)work->actor;
        work->second=CreateOppositePhaseChild((TaskCallback)RunSecondStageChild,20,second_event,parent);
        ++event->phase;
        break;
    case 261:
        work->second=PollAndReleaseChild(work->second);
        if(work->second!=0) break;
        third_event[1]=(u32)work->actor;
        work->third=CreateOppositePhaseChild((TaskCallback)RunThirdStageChild,16,third_event,parent);
        ++event->phase;
        break;
    case 262:
        work->third=PollAndReleaseChild(work->third);
        if(work->third!=0) break;
        fourth_event[1]=(u32)work->actor;
        work->fourth=CreateOppositePhaseChild((TaskCallback)RunFourthStageChild,16,fourth_event,parent);
        ++event->phase;
        break;
    case 263:
        work->fourth=PollAndReleaseChild(work->fourth);
        if(work->fourth!=0) break;
        ++event->phase;
        break;
    case 264:
        event->phase=phase+1;
        break;
    case 265: {
        const u16 *source;
        u16 *saved;
        SelectActorFlag256(work->record,0);
        source=GetDefinitionValues();
        saved=AllocateSequenceBuffer(192);
        work->saved_values=saved;
        MapDefinitionValues(source,saved,95,8);
        work->range=BeginSavedRangeTransition(1,95,30,work->saved_values);
        ++event->phase;
        break;
    }
    case 266:
        work->range=ReleaseCompletedRangeRequest(work->range);
        if(work->range!=0) break;
        FreeSequenceBuffer(work->saved_values);
        work->delay=1;
        ++event->phase;
        break;
    case 267: {
        u32 remaining=work->delay-1;
        work->delay=(u16)remaining;
        if((u16)remaining!=0) break;
        work->target=GetDefinitionTarget(work->actor,work->cursor);
        SelectObjectViewport(ReadOptionalTargetObject(work->target));
        ++event->phase;
        /* Original same-call fall-through into the readiness/motion stage. */
    }
    case 268: {
        TaskNode **motions;
        register u32 cursor __asm__("r2");
        u32 parity,flags;
        if((u8)QuerySequenceReadiness()!=0) break;
        motions=work->motions;
        PollMotionArray(motions,4);
        cursor=work->cursor;
        /* The original post-poll byte snapshot occupies full R2 through its
         * parity and later mask6 uses. This is initialized before this
         * input-only constraint; no incoming R2 or outgoing count is live. */
        __asm__("" : : "r" (cursor));
        parity=cursor&1;
        flags=2;
        if(parity!=0) flags=4;
        motions[work->cursor&3]=CreateTargetMotion(work->target,gAuthoredTargetMotion,
                          (u8)(12-(cursor&6)),10,flags|8,parent,10);
        ++work->cursor;
        if(work->cursor==work->count) ++event->phase;
        else {
            work->delay=40;
            event->phase=267;
        }
        break;
    }
    case 269:
        if((u8)PollMotionArray(work->motions,4)!=0) event->phase=2;
        break;
    }
    return 0;
}
