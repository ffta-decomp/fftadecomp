typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
struct DirectionEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct DirectionWork {
    s16 x,y;
    u16 timer;
    u8 variant,ready;
    void *actor,*target_projection,*target,*record;
    TaskNode *initial;
    void *projected;
    TaskNode *sequence,*auxiliary,*actor_sequence,*stage;
};
typedef char DirectionEventMustBe28[sizeof(struct DirectionEvent)==28?1:-1];
typedef char DirectionWorkMustBe48[sizeof(struct DirectionWork)==48?1:-1];
extern const u8 DirectionInitialResource[],DirectionSetupResource[],DirectionStageResource[],DirectionSecondaryResource[];
extern const u8 DirectionChoices[],DirectionOptions[];
extern TaskNode *CreateDirectionInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDirectionInputs(void);
extern TaskNode *PollDirectionInitial(TaskNode *);
extern u32 ShouldSkipDirectionSequence(void *);
extern TaskNode *CreateDirectionActorSequence(void *,void **,u16,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void ConfigureDirectionRecord(void *,u8);
extern void CopyDirectionTable(void *,const void *,u32);
extern u32 IsDirectionQueueBusy(void);
extern u32 CountDirectionTargets(void *,u8);
extern void *GetDirectionTarget(void *,u8);
extern void *ProjectDirectionTarget(void *,s16 *,s16 *,u8);
extern void GetDirectionRecordCoordinates(void *,s16 *,s16 *);
extern void GetDirectionActorCoordinates(void *,s16 *,s16 *,s16 *);
/* Caller supplies full SIGN8 carriers; helper consumes their low bytes. */
extern u32 ChooseDirectionFromByteDifference(int,int);
extern void *CreateDirectionProjection(const void *,u8,s16,s16,u32,u32,u32,u32);
extern void ConfigureDirectionProjection(void *,u8);
extern TaskNode *CreateDirectionAuxiliary(void *,u32,u32,TaskNode *);
extern TaskNode *CreateDirectionSequence(const void *,TaskNode *);
extern TaskNode *CreateDirectionStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollDirectionAuxiliary(TaskNode *);
extern TaskNode *CreateDirectionSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern u32 IsDirectionActorFinished(void *);
extern TaskNode *PollDirectionSequence(TaskNode *);
extern void *PollDirectionProjection(void *);

u32 AdvanceRelativeDirectionTargetSequence(TaskNode *,struct DirectionEvent *,struct DirectionWork *)
    __asm__("OriginalActionCallback_000FB0B4");
u32 AdvanceRelativeDirectionTargetSequence(TaskNode *task,struct DirectionEvent *event,
                                          struct DirectionWork *work)
{
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=2;
        if(work->variant!=0) count=0;
        work->initial=CreateDirectionInitial(work->record,DirectionInitialResource,count,0,0,task);
        break;
    }
    case 1:
        CleanupDirectionInputs();
        break;
    case 256: {
        u32 skip;
        work->initial=PollDirectionInitial(work->initial);
        if(work->initial!=0) break;
        skip=(u8)ShouldSkipDirectionSequence(work->record);
        if(skip!=0) {
            event->phase=2;
            break;
        }
        work->actor_sequence=CreateDirectionActorSequence(work->record,&work->actor,32775,1,
                              &work->ready,DirectionSetupResource,5,skip,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->ready==0) break;
        ConfigureDirectionRecord(work->record,0);
        work->timer=10;
        event->phase++;
        /* Same invocation continues through both table copies and decrement. */
    case 258: {
        u8 choices[4],options[4];
        s16 record0,record1,actor0,actor1,actor2;
        u8 *option_base;
        u32 queued;
        u8 direction;
        CopyDirectionTable(choices,DirectionChoices,4);
        option_base=options;
        CopyDirectionTable(option_base,DirectionOptions,4);
        if(work->timer!=0) {
            u32 raw_timer;
            raw_timer=(u32)work->timer-1;
            work->timer=raw_timer;
            if((u16)raw_timer!=0) break;
        }
        queued=(u8)IsDirectionQueueBusy();
        if(queued!=0) break;
        if((u8)CountDirectionTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        work->target=GetDirectionTarget(work->record,0);
        work->target_projection=ProjectDirectionTarget(work->target,&work->x,&work->y,0);
        GetDirectionRecordCoordinates(work->record,&record0,&record1);
        GetDirectionActorCoordinates(work->actor,&actor0,&actor1,&actor2);
        direction=(u8)ChooseDirectionFromByteDifference(
             (s8)(*(u8 *)&record0-*(u8 *)&actor0),
             (s8)(*(u8 *)&record1-*(u8 *)&actor2));
        work->projected=CreateDirectionProjection((const void *)0x08502560,
             *(u8 *)((u32)choices+(u32)direction),work->x,work->y,993,6,queued,1);
        ConfigureDirectionProjection(work->projected,*(u8 *)((u32)option_base+(u32)direction));
        work->auxiliary=CreateDirectionAuxiliary(work->target,11,0,task);
        if(work->auxiliary!=0) {
            work->sequence=CreateDirectionSequence((const void *)0x0894848C,task);
            work->stage=CreateDirectionStage(DirectionStageResource,1,4,0,task);
        }
        event->phase++;
        break;
    }
    case 259: {
        TaskNode *completed;
        completed=PollDirectionAuxiliary(work->auxiliary);
        work->auxiliary=completed;
        if(completed!=0) break;
        work->auxiliary=CreateDirectionSecondary(work->target,DirectionSecondaryResource,12,0,
                                                12,task,(u32)completed);
        event->phase++;
        break;
    }
    case 260:
        if((u8)IsDirectionActorFinished(work->actor)==0) break;
        work->sequence=PollDirectionSequence(work->sequence);
        if(work->sequence!=0) break;
        work->projected=PollDirectionProjection(work->projected);
        if(work->projected!=0) break;
        work->auxiliary=PollDirectionAuxiliary(work->auxiliary);
        if(work->auxiliary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateDirectionInitial\n.thumb_set CreateDirectionInitial,0x80e03f9");
__asm__(".global CleanupDirectionInputs\n.thumb_set CleanupDirectionInputs,0x80d38b5");
__asm__(".global PollDirectionInitial\n.thumb_set PollDirectionInitial,0x80e05dd");
__asm__(".global ShouldSkipDirectionSequence\n.thumb_set ShouldSkipDirectionSequence,0x80d3b55");
__asm__(".global CreateDirectionActorSequence\n.thumb_set CreateDirectionActorSequence,0x80ddf69");
__asm__(".global ConfigureDirectionRecord\n.thumb_set ConfigureDirectionRecord,0x80dbffd");
__asm__(".global CopyDirectionTable\n.thumb_set CopyDirectionTable,0x81443fd");
__asm__(".global IsDirectionQueueBusy\n.thumb_set IsDirectionQueueBusy,0x80d8b4d");
__asm__(".global CountDirectionTargets\n.thumb_set CountDirectionTargets,0x80d8859");
__asm__(".global GetDirectionTarget\n.thumb_set GetDirectionTarget,0x80dd4a5");
__asm__(".global ProjectDirectionTarget\n.thumb_set ProjectDirectionTarget,0x80dd749");
__asm__(".global GetDirectionRecordCoordinates\n.thumb_set GetDirectionRecordCoordinates,0x80d8b5d");
__asm__(".global GetDirectionActorCoordinates\n.thumb_set GetDirectionActorCoordinates,0x80dbd79");
__asm__(".global ChooseDirectionFromByteDifference\n.thumb_set ChooseDirectionFromByteDifference,0x809d6bd");
__asm__(".global CreateDirectionProjection\n.thumb_set CreateDirectionProjection,0x80d5cc1");
__asm__(".global ConfigureDirectionProjection\n.thumb_set ConfigureDirectionProjection,0x8011119");
__asm__(".global CreateDirectionAuxiliary\n.thumb_set CreateDirectionAuxiliary,0x80df9e5");
__asm__(".global CreateDirectionSequence\n.thumb_set CreateDirectionSequence,0x80d4705");
__asm__(".global CreateDirectionStage\n.thumb_set CreateDirectionStage,0x80dfd8d");
__asm__(".global PollDirectionAuxiliary\n.thumb_set PollDirectionAuxiliary,0x80dba5d");
__asm__(".global CreateDirectionSecondary\n.thumb_set CreateDirectionSecondary,0x80dcfe5");
__asm__(".global IsDirectionActorFinished\n.thumb_set IsDirectionActorFinished,0x80de1f1");
__asm__(".global PollDirectionSequence\n.thumb_set PollDirectionSequence,0x80d4775");
__asm__(".global PollDirectionProjection\n.thumb_set PollDirectionProjection,0x8011485");
__asm__(".global DirectionInitialResource\n.set DirectionInitialResource,0x839cbb4");
__asm__(".global DirectionSetupResource\n.set DirectionSetupResource,0x839cbe0");
__asm__(".global DirectionStageResource\n.set DirectionStageResource,0x839cbe4");
__asm__(".global DirectionSecondaryResource\n.set DirectionSecondaryResource,0x839cbcc");
__asm__(".global DirectionChoices\n.set DirectionChoices,0x8149d78");
__asm__(".global DirectionOptions\n.set DirectionOptions,0x8149d7c");
