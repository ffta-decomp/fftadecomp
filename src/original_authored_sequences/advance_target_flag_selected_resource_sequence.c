typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
struct FlagSequenceEvent {u16 phase,unknown02; void *record; u8 unknown08[12]; u16 definition,variant; u8 unknown18[4];};
struct FlagSequenceWork {
    u8 variant,unknown01;
    u16 timer;
    s16 x,y;
    u8 ready,unknown09[3];
    u32 positioned_output;
    TaskNode *positioned;
    void *record,*actor,*projected;
    TaskNode *initial,*secondary,*actor_sequence,*stage;
};
struct FlagResourcePair {const void *items[2];};
typedef char FlagEventSize[sizeof(struct FlagSequenceEvent)==28?1:-1];
typedef char FlagWorkSize[sizeof(struct FlagSequenceWork)==48?1:-1];
typedef char FlagPairSize[sizeof(struct FlagResourcePair)==8?1:-1];
extern const struct FlagResourcePair FlagCopiedResources;
extern const u8 FlagInitialResource[],FlagSetupResource[],FlagSecondaryResource[],FlagStageRows[];
extern TaskNode *CreateFlagInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupFlagInputs(void);
extern TaskNode *PollFlagInitial(TaskNode *);
extern u32 ShouldSkipFlagSequence(void *);
extern TaskNode *CreateFlagActorSequence(void *,void **,u16,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void ConfigureFlagRecord(void *,u8,u8);
extern u32 IsFlagQueueBusy(void);
extern u32 CountFlagTargets(void *,u8);
extern void *GetFlagTarget(void *,u8);
extern void *ProjectFlagTarget(void *,s16 *,s16 *,u8);
extern u32 TestFlagTargetBit7(void *);
extern TaskNode *CreateFlagPositioned(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateFlagSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *CreateFlagStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollFlagPositioned(TaskNode *);
extern u32 IsFlagActorFinished(void *);
extern TaskNode *PollFlagSecondary(TaskNode *);

u32 AdvanceTargetFlagSelectedResourceSequence(TaskNode *,struct FlagSequenceEvent *,struct FlagSequenceWork *)
    __asm__("OriginalActionCallback_000FF76C");
u32 AdvanceTargetFlagSelectedResourceSequence(TaskNode *task,struct FlagSequenceEvent *event,struct FlagSequenceWork *work)
{
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=2;
        if(work->variant!=0) count=0;
        work->initial=CreateFlagInitial(work->record,FlagInitialResource,count,0,0,task);
        break;
    }
    case 1:
        CleanupFlagInputs();
        break;
    case 256: {
        u32 skip;
        work->initial=PollFlagInitial(work->initial);
        if(work->initial!=0) break;
        skip=(u8)ShouldSkipFlagSequence(work->record);
        if(skip!=0) {
            event->phase=2;
            break;
        }
        work->actor_sequence=CreateFlagActorSequence(work->record,&work->actor,32775,1,&work->ready,
                                                      FlagSetupResource,5,skip,task);
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
        ConfigureFlagRecord(work->record,0,2);
        work->timer=16;
        event->phase++;
        break;
    }
    case 259: {
        struct FlagResourcePair resources;
        void *target;
        u32 kind;
        resources=FlagCopiedResources;
        if(work->timer!=0) {
            u32 raw_timer;
            raw_timer=(u32)work->timer-1;
            work->timer=raw_timer;
            if((u16)raw_timer!=0) break;
        }
        if((u8)IsFlagQueueBusy()!=0) break;
        if((u8)CountFlagTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        target=GetFlagTarget(work->record,0);
        work->projected=ProjectFlagTarget(target,&work->x,&work->y,0);
        kind=0;
        if((u8)TestFlagTargetBit7(target)==0) kind=1;
        work->positioned=CreateFlagPositioned(work->x,work->y,0,1,1,&work->positioned_output,
                                              resources.items[kind],task);
        work->secondary=CreateFlagSecondary(target,FlagSecondaryResource,12,82,4,task,80);
        work->stage=CreateFlagStage((const void *)((u32)FlagStageRows+kind*8),1,4,0,task);
        event->phase++;
        break;
    }
    case 260:
        work->positioned=PollFlagPositioned(work->positioned);
        if(work->positioned!=0) break;
        if((u8)IsFlagActorFinished(work->actor)==0) break;
        work->secondary=PollFlagSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateFlagInitial\n.thumb_set CreateFlagInitial,0x80e03f9");
__asm__(".global CleanupFlagInputs\n.thumb_set CleanupFlagInputs,0x80d38b5");
__asm__(".global PollFlagInitial\n.thumb_set PollFlagInitial,0x80e05dd");
__asm__(".global ShouldSkipFlagSequence\n.thumb_set ShouldSkipFlagSequence,0x80d3b55");
__asm__(".global CreateFlagActorSequence\n.thumb_set CreateFlagActorSequence,0x80ddf69");
__asm__(".global ConfigureFlagRecord\n.thumb_set ConfigureFlagRecord,0x80dc12d");
__asm__(".global IsFlagQueueBusy\n.thumb_set IsFlagQueueBusy,0x80d8b4d");
__asm__(".global CountFlagTargets\n.thumb_set CountFlagTargets,0x80d8859");
__asm__(".global GetFlagTarget\n.thumb_set GetFlagTarget,0x80dd4a5");
__asm__(".global ProjectFlagTarget\n.thumb_set ProjectFlagTarget,0x80dd749");
__asm__(".global TestFlagTargetBit7\n.thumb_set TestFlagTargetBit7,0x80dd581");
__asm__(".global CreateFlagPositioned\n.thumb_set CreateFlagPositioned,0x80d6099");
__asm__(".global CreateFlagSecondary\n.thumb_set CreateFlagSecondary,0x80dcfe5");
__asm__(".global CreateFlagStage\n.thumb_set CreateFlagStage,0x80dfd8d");
__asm__(".global PollFlagPositioned\n.thumb_set PollFlagPositioned,0x80d6135");
__asm__(".global IsFlagActorFinished\n.thumb_set IsFlagActorFinished,0x80de245");
__asm__(".global PollFlagSecondary\n.thumb_set PollFlagSecondary,0x80dba5d");
__asm__(".global FlagCopiedResources\n.set FlagCopiedResources,0x8149dd0");
__asm__(".global FlagInitialResource\n.set FlagInitialResource,0x839e3c0");
__asm__(".global FlagSetupResource\n.set FlagSetupResource,0x839e41c");
__asm__(".global FlagSecondaryResource\n.set FlagSecondaryResource,0x839e408");
__asm__(".global FlagStageRows\n.set FlagStageRows,0x839e420");
__asm__(".balign 4,0");
