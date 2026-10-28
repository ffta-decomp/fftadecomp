typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct TargetSequenceEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[14];
    u16 variant;
    u8 unknown18[4];
};
struct TargetChildEvent {
    u32 unknown00;
    void *record,*actor;
    u8 unknown0c[8];
    u16 ordinal,delay;
    u32 unknown18;
};
struct TargetSequenceWork {
    u32 unknown00;
    u8 variant,count,cursor,byte_delay;
    u16 delay,unknown0a;
    TaskNode *selector_task,*first_child;
    TaskNode *child_slots[4];
    void *record,*actor;
    TaskNode *initial_effect;
    TaskNode *motion_slots[4];
    TaskNode *sequence;
};
typedef char EventSize[sizeof(struct TargetSequenceEvent)==28?1:-1];
typedef char ChildEventSize[sizeof(struct TargetChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct TargetSequenceWork)==68?1:-1];
extern void CleanupDefinitionInputs(void);
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern u32 IsDefinitionRecordEmpty(void *);
extern u32 ReadDefinitionTargetCount(void *);
extern void *GetActorNestedRecord(void *);
extern void SetNestedRecordCurrentValue(void *,u16);
extern void SelectActorFlag256(void *,u8);
extern TaskNode *CreateOppositePhaseChild(TaskCallback,u16,const u32 *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollAndReleaseChild(TaskNode *);
extern TaskNode *CreateSelectorTask(u32,void *,TaskNode *);
extern TaskNode *PollSelectorTask(TaskNode *);
extern u32 QueryDefinitionTargetCount(void *,u16);
extern void RestoreActorMotionPresentation(void *);
extern void *GetDefinitionTarget(void *,u8);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern u32 SelectDefinitionViewport(void *,u8);
extern u32 QuerySequenceReadiness(void);
extern TaskNode *CreateTargetMotion(void *,const void *,u8,u16,u32,TaskNode *,u32);
extern u32 PollNestedRecordHandles(void *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
extern s32 RunInitialRecordChild(TaskNode *,u16 *,void *);
extern s32 RunDirectionalTargetChild(TaskNode *,u16 *,void *);
extern const u8 gTargetOpeningStage[],gTargetSequenceStage[],gTargetMotionStage[];
__asm__(".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x080e05dd\n"
 ".global IsDefinitionRecordEmpty\n.thumb_set IsDefinitionRecordEmpty,0x080d3b55\n"
 ".global ReadDefinitionTargetCount\n.thumb_set ReadDefinitionTargetCount,0x080dd495\n"
 ".global GetActorNestedRecord\n.thumb_set GetActorNestedRecord,0x080dd47d\n"
 ".global SetNestedRecordCurrentValue\n.thumb_set SetNestedRecordCurrentValue,0x080de10d\n"
 ".global SelectActorFlag256\n.thumb_set SelectActorFlag256,0x080de3bd\n"
 ".global CreateOppositePhaseChild\n.thumb_set CreateOppositePhaseChild,0x08005b6d\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
 ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x080e051d\n"
 ".global CreateSelectorTask\n.thumb_set CreateSelectorTask,0x080f2e41\n"
 ".global PollSelectorTask\n.thumb_set PollSelectorTask,0x080f1211\n"
 ".global QueryDefinitionTargetCount\n.thumb_set QueryDefinitionTargetCount,0x080d8859\n"
 ".global RestoreActorMotionPresentation\n.thumb_set RestoreActorMotionPresentation,0x080de391\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x080dd4a5\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x080e0571\n"
 ".global SelectDefinitionViewport\n.thumb_set SelectDefinitionViewport,0x080dbffd\n"
 ".global QuerySequenceReadiness\n.thumb_set QuerySequenceReadiness,0x080d8b4d\n"
 ".global CreateTargetMotion\n.thumb_set CreateTargetMotion,0x080dcfe5\n"
 ".global PollNestedRecordHandles\n.thumb_set PollNestedRecordHandles,0x080de1f1\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x080dba5d\n"
 ".global RunInitialRecordChild\n.thumb_set RunInitialRecordChild,0x08116f99\n"
 ".global RunDirectionalTargetChild\n.thumb_set RunDirectionalTargetChild,0x081171cd\n"
 ".global gTargetOpeningStage\n.set gTargetOpeningStage,0x083a506c\n"
 ".global gTargetSequenceStage\n.set gTargetSequenceStage,0x083a50d4\n"
 ".global gTargetMotionStage\n.set gTargetMotionStage,0x083a50c0");
s32 AdvanceAuthoredTargetSequence(TaskNode *,struct TargetSequenceEvent *,struct TargetSequenceWork *)
    __asm__("OriginalActionCallback_00117320");
s32 AdvanceAuthoredTargetSequence(TaskNode *parent,struct TargetSequenceEvent *event,
                                  struct TargetSequenceWork *work)
{
    /* Two separately addressed original 28B templates, not a shared case-local
     * scratch object. Unwritten template bytes retain their original status. */
    u32 first_event[7];
    struct TargetChildEvent target_event;
    switch(event->phase) {
    case 0: {
        u16 variant=event->variant;
        void *actor;
        u8 count;
        work->variant=(u8)variant;
        actor=event->actor;
        work->actor=actor;
        count=7;
        if((u8)variant!=0) count=0;
        work->initial_effect=CreateDefinitionEffectTask(actor,gTargetOpeningStage,
                                                         count,0,0,parent);
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256:
        work->initial_effect=PollDefinitionEffect(work->initial_effect);
        if(work->initial_effect!=0) break;
        if((u8)IsDefinitionRecordEmpty(work->actor)!=0) {
            event->phase=2;
            break;
        }
        if(work->variant!=0) {
            work->count=(u8)ReadDefinitionTargetCount(work->actor);
            work->byte_delay=1;
            event->phase=259;
        } else {
            work->record=GetActorNestedRecord(work->actor);
            SetNestedRecordCurrentValue(work->record,36);
            SelectActorFlag256(work->record,1);
            first_event[1]=(u32)work->record;
            work->first_child=CreateOppositePhaseChild((TaskCallback)RunInitialRecordChild,
                                                       52,first_event,parent);
            work->sequence=CreateSequenceStage(gTargetSequenceStage,1,4,0,parent);
            ++event->phase;
        }
        break;
    case 257:
        work->first_child=PollAndReleaseChild(work->first_child);
        if(work->first_child!=0) break;
        work->selector_task=CreateSelectorTask(8,work->actor,parent);
        ++event->phase;
        break;
    case 258: {
        u32 delay,count;
        u16 event_index;
        u8 ordinal;
        work->selector_task=PollSelectorTask(work->selector_task);
        if(work->selector_task!=0) break;
        delay=work->delay;
        if(delay!=0) {
            --delay;
            work->delay=(u16)delay;
            if((u16)delay!=0) break;
        }
        count=QueryDefinitionTargetCount(work->actor,0);
        work->count=(u8)count;
        if((u8)count==0) {
            event->phase=2;
            break;
        }
        RestoreActorMotionPresentation(work->record);
        event_index=0;
        ordinal=0;
        while(ordinal<work->count) {
            TaskNode *child;
            target_event.ordinal=ordinal;
            target_event.delay=event_index;
            target_event.record=GetDefinitionTarget(work->actor,ordinal);
            target_event.actor=work->actor;
            child=CreateOppositePhaseChild((TaskCallback)RunDirectionalTargetChild,
                                            28,(const u32 *)&target_event,parent);
            /* The original index is an arbitrary byte. Four is the later poll
             * count, not a proven dynamic bound: do not clamp the original index. */
            work->child_slots[ordinal]=child;
            ++event_index;
            ++ordinal;
        }
        ++event->phase;
        break;
    }
    case 259:
        if((u8)PollDefinitionTaskArray(work->child_slots,4)!=0) {
            work->byte_delay=1;
            ++event->phase;
        }
        break;
    case 260:
        SelectDefinitionViewport(work->actor,work->cursor);
        ++event->phase;
        /* Original same-call fall-through. */
    case 261: {
        u32 decrement,delay;
        void *target;
        u32 parity,flags;
        TaskNode *motion;
        if((u8)QuerySequenceReadiness()!=0) break;
        decrement=work->byte_delay-1;
        work->byte_delay=(u8)decrement;
        delay=(u8)decrement;
        if(delay!=0) break;
        target=GetDefinitionTarget(work->actor,work->cursor);
        parity=work->cursor&1;
        flags=2;
        if(parity!=0) flags=4;
        motion=CreateTargetMotion(target,gTargetMotionStage,(u8)(12-parity),0,
                                  flags|8,parent,delay);
        work->motion_slots[work->cursor]=motion;
        work->byte_delay=40;
        ++work->cursor;
        if(work->cursor!=work->count) event->phase=260;
        else ++event->phase;
        break;
    }
    case 262: {
        u32 all_done;
        u8 ordinal;
        TaskNode **motion_slots;
        /* The variant path does not initialize record here. Preserve the
         * original helper call; no invented NULL guard or success behavior. */
        if((u8)PollNestedRecordHandles(work->record)==0) break;
        all_done=1;
        ordinal=0;
        motion_slots=work->motion_slots;
        do {
            TaskNode **slot=&motion_slots[ordinal];
            *slot=PollAndReleaseMotion(*slot);
            if(*slot!=0) all_done=0;
            ++ordinal;
        } while(ordinal<=3);
        if(all_done!=0) event->phase=2;
        break;
    }
    }
    return 0;
}
