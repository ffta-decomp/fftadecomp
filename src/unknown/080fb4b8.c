#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
struct ResourceTransitionEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct ResourceTransitionWork {
    s16 x,y;
    u8 variant,ready,unknown06[2];
    void *actor,*projected,*record;
    TaskNode *initial;
    u8 positioned_output[12];
    TaskNode *positioned;
    void *resource;
    TaskNode *sequence,*palette,*secondary,*actor_sequence,*stage;
};
typedef char TransitionEventSize[sizeof(struct ResourceTransitionEvent)==28?1:-1];
typedef char TransitionWorkSize[sizeof(struct ResourceTransitionWork)==64?1:-1];
extern const u8 ResourceTransitionInitial[],ResourceTransitionPositionedFirst[],ResourceTransitionPositionedTarget[];
extern const u8 ResourceTransitionActor[],ResourceTransitionSecondary[],ResourceTransitionStageFirst[],ResourceTransitionStageTarget[];
extern TaskNode *CreateResourceTransitionInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupResourceTransitionInputs(void);
extern TaskNode *PollResourceTransitionInitial(TaskNode *);
extern u32 SkipResourceTransition(void *);
extern void *GetResourceTransitionActor(void *);
extern void SetResourceTransitionActorMode(void *,u32);
extern void ProjectResourceTransitionActor(void *,s16 *,s16 *);
extern void ConfigureResourceTransitionCoordinates(u8,u8,u16,s16,s16);
extern void *CreateResourceTransitionResource(u8,const void *,u16,u8);
extern u32 ResourceTransitionMask(u8);
extern u16 ResourceTransitionDisplayFlags;
extern TaskNode *CreateResourceTransitionSequence(const void *,TaskNode *);
/* Preserve actual caller's full SIGN16 x/y carriers; helper consumes LOW16 y. */
extern TaskNode *CreateResourceTransitionPositioned(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateResourceTransitionPalette(const void *,TaskNode *,u16);
extern TaskNode *CreateResourceTransitionStage(const void *,u8,u16,u16,TaskNode *);
extern void *PollResourceTransitionResource(void *,u8);
extern TaskNode *PollResourceTransitionSequence(TaskNode *);
extern TaskNode *PollResourceTransitionPalette(TaskNode *);
extern TaskNode *PollResourceTransitionPositioned(TaskNode *);
extern TaskNode *CreateResourceTransitionActorSequence(void *,void **,u16,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void ConfigureResourceTransitionRecord(void *,u8);
extern u32 ResourceTransitionQueueBusy(void);
extern u32 CountResourceTransitionTargets(void *,u8);
extern void *GetResourceTransitionTarget(void *,u8);
extern void *ProjectResourceTransitionTarget(void *,s16 *,s16 *,u8);
extern TaskNode *CreateResourceTransitionSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern u32 IsResourceTransitionActorFinished(void *);
extern TaskNode *PollResourceTransitionSecondary(TaskNode *);

u32 AdvanceResourceTransitionTargetSequence(TaskNode *,struct ResourceTransitionEvent *,struct ResourceTransitionWork *)
    __asm__("OriginalActionCallback_000FB4B8");
u32 AdvanceResourceTransitionTargetSequence(TaskNode *task,struct ResourceTransitionEvent *event,
                                           struct ResourceTransitionWork *work)
{
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=4;
        if(work->variant!=0) count=0;
        work->initial=CreateResourceTransitionInitial(work->record,ResourceTransitionInitial,count,0,0,task);
        break;
    }
    case 1:
        CleanupResourceTransitionInputs();
        break;
    case 256: {
        s16 x,y;
        u32 mask;
        register u32 control __asm__("r1");
        work->initial=PollResourceTransitionInitial(work->initial);
        if(work->initial!=0) break;
        if((u8)SkipResourceTransition(work->record)!=0) {
            event->phase=2;
            break;
        }
        work->actor=GetResourceTransitionActor(work->record);
        SetResourceTransitionActorMode(work->actor,36);
        ProjectResourceTransitionActor(work->actor,&x,&y);
        ConfigureResourceTransitionCoordinates(0,2,0,x,y);
        work->resource=CreateResourceTransitionResource(0,(const void *)0x088EF398,959,6);
        mask=ResourceTransitionMask(2);
        control=ResourceTransitionDisplayFlags;
        __asm__("" : "+r"(control));
        control|=mask;
        ResourceTransitionDisplayFlags=control;
        work->sequence=CreateResourceTransitionSequence((const void *)0x0894D90C,task);
        work->positioned=CreateResourceTransitionPositioned(x,y,0,1,1,work->positioned_output,
                                                         ResourceTransitionPositionedFirst,task);
        work->palette=CreateResourceTransitionPalette((const void *)0x0894AAB0,task,15);
        work->stage=CreateResourceTransitionStage(ResourceTransitionStageFirst,1,4,0,task);
        event->phase++;
        break;
    }
    case 257: {
        u32 mask;
        TaskNode *completed;
        work->resource=PollResourceTransitionResource(work->resource,0);
        if(work->resource!=0) break;
        work->sequence=PollResourceTransitionSequence(work->sequence);
        if(work->sequence!=0) break;
        work->palette=PollResourceTransitionPalette(work->palette);
        if(work->palette!=0) break;
        mask=ResourceTransitionMask(2);
        ResourceTransitionDisplayFlags&=~mask;
        completed=PollResourceTransitionPositioned(work->positioned);
        work->positioned=completed;
        if(completed!=0) break;
        work->actor_sequence=CreateResourceTransitionActorSequence(work->record,0,32775,1,&work->ready,
                                             ResourceTransitionActor,5,(u32)completed,task);
        event->phase++;
        break;
    }
    case 258:
        if(work->ready==0) break;
        ConfigureResourceTransitionRecord(work->record,0);
        event->phase++;
        /* Original same-call fallthrough into target setup. */
    case 259: {
        void *target;
        if((u8)ResourceTransitionQueueBusy()!=0) break;
        if((u8)CountResourceTransitionTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        target=GetResourceTransitionTarget(work->record,0);
        work->projected=ProjectResourceTransitionTarget(target,&work->x,&work->y,0);
        work->positioned=CreateResourceTransitionPositioned(work->x,work->y,0,1,3,
                                              work->positioned_output,ResourceTransitionPositionedTarget,task);
        work->secondary=CreateResourceTransitionSecondary(target,ResourceTransitionSecondary,12,38,4,task,38);
        work->stage=CreateResourceTransitionStage(ResourceTransitionStageTarget,3,4,0,task);
        event->phase++;
        break;
    }
    case 260:
        if((u8)IsResourceTransitionActorFinished(work->actor)==0) break;
        work->positioned=PollResourceTransitionPositioned(work->positioned);
        if(work->positioned!=0) break;
        work->secondary=PollResourceTransitionSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateResourceTransitionInitial\n.thumb_set CreateResourceTransitionInitial,0x80e03f9");
__asm__(".global CleanupResourceTransitionInputs\n.thumb_set CleanupResourceTransitionInputs,0x80d38b5");
__asm__(".global PollResourceTransitionInitial\n.thumb_set PollResourceTransitionInitial,0x80e05dd");
__asm__(".global SkipResourceTransition\n.thumb_set SkipResourceTransition,0x80d3b55");
__asm__(".global GetResourceTransitionActor\n.thumb_set GetResourceTransitionActor,0x80dd47d");
__asm__(".global SetResourceTransitionActorMode\n.thumb_set SetResourceTransitionActorMode,0x80de10d");
__asm__(".global ProjectResourceTransitionActor\n.thumb_set ProjectResourceTransitionActor,0x80dbdc9");
__asm__(".global ConfigureResourceTransitionCoordinates\n.thumb_set ConfigureResourceTransitionCoordinates,0x80d49fd");
__asm__(".global CreateResourceTransitionResource\n.thumb_set CreateResourceTransitionResource,0x80d4b65");
__asm__(".global ResourceTransitionMask\n.thumb_set ResourceTransitionMask,0x80035a9");
__asm__(".global CreateResourceTransitionSequence\n.thumb_set CreateResourceTransitionSequence,0x80d3e9d");
__asm__(".global CreateResourceTransitionPositioned\n.thumb_set CreateResourceTransitionPositioned,0x80d6099");
__asm__(".global CreateResourceTransitionPalette\n.thumb_set CreateResourceTransitionPalette,0x80d4725");
__asm__(".global CreateResourceTransitionStage\n.thumb_set CreateResourceTransitionStage,0x80dfd8d");
__asm__(".global PollResourceTransitionResource\n.thumb_set PollResourceTransitionResource,0x80d4d2d");
__asm__(".global PollResourceTransitionSequence\n.thumb_set PollResourceTransitionSequence,0x80d3f09");
__asm__(".global PollResourceTransitionPalette\n.thumb_set PollResourceTransitionPalette,0x80d4775");
__asm__(".global PollResourceTransitionPositioned\n.thumb_set PollResourceTransitionPositioned,0x80d6135");
__asm__(".global CreateResourceTransitionActorSequence\n.thumb_set CreateResourceTransitionActorSequence,0x80ddf69");
__asm__(".global ConfigureResourceTransitionRecord\n.thumb_set ConfigureResourceTransitionRecord,0x80dbffd");
__asm__(".global ResourceTransitionQueueBusy\n.thumb_set ResourceTransitionQueueBusy,0x80d8b4d");
__asm__(".global CountResourceTransitionTargets\n.thumb_set CountResourceTransitionTargets,0x80d8859");
__asm__(".global GetResourceTransitionTarget\n.thumb_set GetResourceTransitionTarget,0x80dd4a5");
__asm__(".global ProjectResourceTransitionTarget\n.thumb_set ProjectResourceTransitionTarget,0x80dd749");
__asm__(".global CreateResourceTransitionSecondary\n.thumb_set CreateResourceTransitionSecondary,0x80dcfe5");
__asm__(".global IsResourceTransitionActorFinished\n.thumb_set IsResourceTransitionActorFinished,0x80de1f1");
__asm__(".global PollResourceTransitionSecondary\n.thumb_set PollResourceTransitionSecondary,0x80dba5d");
__asm__(".global ResourceTransitionInitial\n.set ResourceTransitionInitial,0x839ccd0");
__asm__(".global ResourceTransitionPositionedFirst\n.set ResourceTransitionPositionedFirst,0x839cd00");
__asm__(".global ResourceTransitionPositionedTarget\n.set ResourceTransitionPositionedTarget,0x839cd18");
__asm__(".global ResourceTransitionActor\n.set ResourceTransitionActor,0x839cd74");
__asm__(".global ResourceTransitionSecondary\n.set ResourceTransitionSecondary,0x839cd60");
__asm__(".global ResourceTransitionStageFirst\n.set ResourceTransitionStageFirst,0x839cd78");
__asm__(".global ResourceTransitionStageTarget\n.set ResourceTransitionStageTarget,0x839cd80");
__asm__(".global ResourceTransitionDisplayFlags\n.set ResourceTransitionDisplayFlags,0x03000940");
__asm__(".balign 4,0");
