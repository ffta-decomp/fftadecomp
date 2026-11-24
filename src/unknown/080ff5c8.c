#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
struct DelayedEvent {u16 phase,unknown02; void *record; u8 unknown08[12]; u16 definition,variant; u8 unknown18[4];};
struct DelayedWork {
    u8 variant,index,count,unknown03;
    u16 timer;
    u8 unknown06[4],ready,unknown11;
    TaskNode *child;
    void *record,*actor;
    TaskNode *initial,*secondary,*actor_sequence;
};
typedef char DelayedEventSize[sizeof(struct DelayedEvent)==28?1:-1];
typedef char DelayedWorkSize[sizeof(struct DelayedWork)==36?1:-1];
extern const u8 DelayedInitialResource[],DelayedSetupResource[],DelayedSecondaryResource[];
extern TaskNode *CreateDelayedInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDelayedInputs(void);
extern TaskNode *PollDelayedInitial(TaskNode *);
extern u32 ShouldSkipDelayedSequence(void *);
extern TaskNode *CreateDelayedActorSequence(void *,void **,u16,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void ConfigureDelayedRecord(void *,u8,u8);
extern u32 IsDelayedQueueBusy(void);
extern u32 CountDelayedTargets(void *,u8);
extern void *GetDelayedTarget(void *,u8);
extern u32 DelayedVariantChild(TaskNode *,struct DelayedEvent *,void *);
extern TaskNode *CreateDelayedChild(u32 (*)(TaskNode *,struct DelayedEvent *,void *),u32,struct DelayedEvent *,TaskNode *);
extern TaskNode *CreateDelayedSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *PollDelayedChild(TaskNode *);
extern u32 IsDelayedActorFinished(void *);
extern TaskNode *PollDelayedSecondary(TaskNode *);

u32 AdvanceVariantDelayedTargetChild(TaskNode *,struct DelayedEvent *,struct DelayedWork *)
    __asm__("OriginalActionCallback_000FF5C8");
u32 AdvanceVariantDelayedTargetChild(TaskNode *task,struct DelayedEvent *event,struct DelayedWork *work)
{
    switch(event->phase) {
    case 0: {
        u8 count;
        work->index=(u8)event->definition+86;
        work->variant=event->variant;
        work->record=event->record;
        count=5;
        if(work->variant!=0) count=0;
        work->initial=CreateDelayedInitial(work->record,DelayedInitialResource,count,0,0,task);
        break;
    }
    case 1:
        CleanupDelayedInputs();
        break;
    case 256: {
        u32 skip;
        work->initial=PollDelayedInitial(work->initial);
        if(work->initial!=0) break;
        skip=(u8)ShouldSkipDelayedSequence(work->record);
        if(skip!=0) {
            event->phase=2;
            break;
        }
        work->actor_sequence=CreateDelayedActorSequence(work->record,&work->actor,32775,1,&work->ready,
                                                         DelayedSetupResource,5,skip,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->ready==0) break;
        work->timer=16;
        event->phase++;
        break;
    case 258: {
        u32 raw_timer;
        raw_timer=(u32)work->timer-1;
        work->timer=raw_timer;
        if((u16)raw_timer!=0) break;
        ConfigureDelayedRecord(work->record,0,2);
        work->timer=16;
        event->phase++;
        break;
    }
    case 259: {
        struct DelayedEvent child_event;
        void *target;
        if(work->timer!=0) {
            u32 raw_timer;
            raw_timer=(u32)work->timer-1;
            work->timer=raw_timer;
            if((u16)raw_timer!=0) break;
        }
        if((u8)IsDelayedQueueBusy()!=0) break;
        work->count=CountDelayedTargets(work->record,0);
        if(work->count==0) {
            event->phase=2;
            break;
        }
        target=GetDelayedTarget(work->record,0);
        child_event.definition=work->index;
        child_event.record=target;
        work->child=CreateDelayedChild(DelayedVariantChild,64,&child_event,task);
        work->secondary=CreateDelayedSecondary(target,DelayedSecondaryResource,12,184,4,task,184);
        event->phase++;
        break;
    }
    case 260:
        work->child=PollDelayedChild(work->child);
        if(work->child!=0) break;
        if((u8)IsDelayedActorFinished(work->actor)==0) break;
        work->secondary=PollDelayedSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateDelayedInitial\n.thumb_set CreateDelayedInitial,0x80e03f9");
__asm__(".global CleanupDelayedInputs\n.thumb_set CleanupDelayedInputs,0x80d38b5");
__asm__(".global PollDelayedInitial\n.thumb_set PollDelayedInitial,0x80e05dd");
__asm__(".global ShouldSkipDelayedSequence\n.thumb_set ShouldSkipDelayedSequence,0x80d3b55");
__asm__(".global CreateDelayedActorSequence\n.thumb_set CreateDelayedActorSequence,0x80ddf69");
__asm__(".global ConfigureDelayedRecord\n.thumb_set ConfigureDelayedRecord,0x80dc12d");
__asm__(".global IsDelayedQueueBusy\n.thumb_set IsDelayedQueueBusy,0x80d8b4d");
__asm__(".global CountDelayedTargets\n.thumb_set CountDelayedTargets,0x80d8859");
__asm__(".global GetDelayedTarget\n.thumb_set GetDelayedTarget,0x80dd4a5");
__asm__(".global DelayedVariantChild\n.thumb_set DelayedVariantChild,0x80ff2c5");
__asm__(".global CreateDelayedChild\n.thumb_set CreateDelayedChild,0x8005b6d");
__asm__(".global CreateDelayedSecondary\n.thumb_set CreateDelayedSecondary,0x80dcfe5");
__asm__(".global PollDelayedChild\n.thumb_set PollDelayedChild,0x80e051d");
__asm__(".global IsDelayedActorFinished\n.thumb_set IsDelayedActorFinished,0x80de245");
__asm__(".global PollDelayedSecondary\n.thumb_set PollDelayedSecondary,0x80dba5d");
__asm__(".global DelayedInitialResource\n.set DelayedInitialResource,0x839e2bc");
__asm__(".global DelayedSetupResource\n.set DelayedSetupResource,0x839e354");
__asm__(".global DelayedSecondaryResource\n.set DelayedSecondaryResource,0x839e340");
__asm__(".balign 4,0");
