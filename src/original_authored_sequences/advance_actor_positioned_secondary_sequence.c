typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
struct PositionedEvent {u16 phase,unknown02; void *record; u8 unknown08[12]; u16 definition,variant; u8 unknown18[4];};
struct PositionedWork {
    u8 variant,unknown01[3];
    void *actor,*record;
    TaskNode *initial;
    u8 positioned_output[8];
    TaskNode *positioned,*secondary,*stage;
};
typedef char PositionedEventSize[sizeof(struct PositionedEvent)==28?1:-1];
typedef char PositionedWorkSize[sizeof(struct PositionedWork)==36?1:-1];
extern const u8 PositionedInitialResource[],PositionedTaskResource[],PositionedStageResource[],PositionedSecondaryResource[];
extern TaskNode *CreatePositionedInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupPositionedInputs(void);
extern TaskNode *PollPositionedInitial(TaskNode *);
extern u32 ShouldSkipPositionedSequence(void *);
extern void *GetPositionedActor(void *);
extern void SetPositionedActorMode(void *,u32);
extern void SetPositionedActorOption(void *,u8);
extern void ProjectPositionedActor(void *,s16 *,s16 *);
extern TaskNode *CreatePositionedSequence(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreatePositionedStage(const void *,u8,u16,u16,TaskNode *);
extern u32 CountPositionedTargets(void *,u8);
extern TaskNode *PollPositionedSequence(TaskNode *);
extern void *GetPositionedTarget(void *,u8);
extern TaskNode *CreatePositionedSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *PollPositionedSecondary(TaskNode *);

u32 AdvanceActorPositionedSecondarySequence(TaskNode *,struct PositionedEvent *,struct PositionedWork *)
    __asm__("OriginalActionCallback_000FF180");
u32 AdvanceActorPositionedSecondarySequence(TaskNode *task,struct PositionedEvent *event,struct PositionedWork *work)
{
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=3;
        if(work->variant!=0) count=0;
        work->initial=CreatePositionedInitial(work->record,PositionedInitialResource,count,0,0,task);
        break;
    }
    case 1:
        CleanupPositionedInputs();
        break;
    case 256: {
        s16 x,y;
        work->initial=PollPositionedInitial(work->initial);
        if(work->initial!=0) break;
        if((u8)ShouldSkipPositionedSequence(work->record)!=0) {
            event->phase=2;
            break;
        }
        work->actor=GetPositionedActor(work->record);
        SetPositionedActorMode(work->actor,36);
        SetPositionedActorOption(work->actor,1);
        ProjectPositionedActor(work->actor,&x,&y);
        work->positioned=CreatePositionedSequence(x,y,0,1,2,work->positioned_output,PositionedTaskResource,task);
        work->stage=CreatePositionedStage(PositionedStageResource,1,4,0,task);
        event->phase++;
        break;
    }
    case 257: {
        TaskNode *completed;
        if((u8)CountPositionedTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        completed=PollPositionedSequence(work->positioned);
        work->positioned=completed;
        if(completed!=0) break;
        work->secondary=CreatePositionedSecondary(GetPositionedTarget(work->record,0),
                                                  PositionedSecondaryResource,12,0,4,task,(u32)completed);
        event->phase++;
        break;
    }
    case 258:
        work->secondary=PollPositionedSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreatePositionedInitial\n.thumb_set CreatePositionedInitial,0x80e03f9");
__asm__(".global CleanupPositionedInputs\n.thumb_set CleanupPositionedInputs,0x80d38b5");
__asm__(".global PollPositionedInitial\n.thumb_set PollPositionedInitial,0x80e05dd");
__asm__(".global ShouldSkipPositionedSequence\n.thumb_set ShouldSkipPositionedSequence,0x80d3b55");
__asm__(".global GetPositionedActor\n.thumb_set GetPositionedActor,0x80dd47d");
__asm__(".global SetPositionedActorMode\n.thumb_set SetPositionedActorMode,0x80de10d");
__asm__(".global SetPositionedActorOption\n.thumb_set SetPositionedActorOption,0x80de3bd");
__asm__(".global ProjectPositionedActor\n.thumb_set ProjectPositionedActor,0x80dbdc9");
__asm__(".global CreatePositionedSequence\n.thumb_set CreatePositionedSequence,0x80d6099");
__asm__(".global CreatePositionedStage\n.thumb_set CreatePositionedStage,0x80dfd8d");
__asm__(".global CountPositionedTargets\n.thumb_set CountPositionedTargets,0x80d8859");
__asm__(".global PollPositionedSequence\n.thumb_set PollPositionedSequence,0x80d6135");
__asm__(".global GetPositionedTarget\n.thumb_set GetPositionedTarget,0x80dd4a5");
__asm__(".global CreatePositionedSecondary\n.thumb_set CreatePositionedSecondary,0x80dcfe5");
__asm__(".global PollPositionedSecondary\n.thumb_set PollPositionedSecondary,0x80dba5d");
__asm__(".global PositionedInitialResource\n.set PositionedInitialResource,0x839e20c");
__asm__(".global PositionedTaskResource\n.set PositionedTaskResource,0x839e230");
__asm__(".global PositionedStageResource\n.set PositionedStageResource,0x839e274");
__asm__(".global PositionedSecondaryResource\n.set PositionedSecondaryResource,0x839e260");
__asm__(".balign 4,0");
