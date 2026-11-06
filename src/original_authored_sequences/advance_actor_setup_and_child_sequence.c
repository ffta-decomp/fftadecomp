typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct ActorSetupEvent {
    u16 phase, unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition, variant;
    u8 unknown18[4];
};
struct ActorSetupWork {
    u8 variant, unknown01;
    u16 timer;
    void *actor, *record;
    TaskNode *initial;
    void *resource;
    TaskNode *projected, *child, *stage;
};
typedef char ActorSetupEventMustBe28[sizeof(struct ActorSetupEvent)==28?1:-1];
typedef char ActorSetupWorkMustBe32[sizeof(struct ActorSetupWork)==32?1:-1];
extern TaskNode *CreateActorSetupInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupActorSetupInputs(void);
extern TaskNode *PollActorSetupInitial(TaskNode *);
extern u32 IsActorSetupUnavailable(void *);
extern void *GetActorSetupActor(void *);
extern void SetActorSetupParameter(void *,u8);
extern void SetActorSetupPhase(void *,u8);
extern void ProjectActorSetupPosition(void *,s16 *,s16 *);
extern TaskNode *CreateActorSetupProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateActorSetupStage(const void *,u8,u16,u16,TaskNode *);
extern u32 CountActorSetupTargets(void *,u8);
extern u32 ActorSetupChild(TaskNode *,struct ActorSetupEvent *,void *);
extern TaskNode *CreateActorSetupTask(u32 (*)(TaskNode *,struct ActorSetupEvent *,void *),u32,struct ActorSetupEvent *,TaskNode *);
extern TaskNode *PollActorSetupProjected(TaskNode *);
extern TaskNode *PollActorSetupChild(TaskNode *);

u32 AdvanceActorSetupAndChildSequence(TaskNode *,struct ActorSetupEvent *,struct ActorSetupWork *)
    __asm__("OriginalActionCallback_000F7160");
u32 AdvanceActorSetupAndChildSequence(TaskNode *task,struct ActorSetupEvent *event,
                                    struct ActorSetupWork *work)
{
    s16 x, y;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=6;
        if(work->variant!=0) count=0;
        work->initial=CreateActorSetupInitial(work->record,(const void *)0x0839BAA8,count,0,0,task);
        break;
    }
    case 1:
        CleanupActorSetupInputs();
        break;
    case 256:
        work->initial=PollActorSetupInitial(work->initial);
        if(work->initial!=0) break;
        if((u8)IsActorSetupUnavailable(work->record)!=0) {
            event->phase=2;
            break;
        }
        work->actor=GetActorSetupActor(work->record);
        SetActorSetupParameter(work->actor,36);
        SetActorSetupPhase(work->actor,1);
        ProjectActorSetupPosition(work->actor,&x,&y);
        work->projected=CreateActorSetupProjected(x,y,0,1,1,&work->resource,
                                                 (const void *)0x0839BAF0,task);
        work->stage=CreateActorSetupStage((const void *)0x0839BB08,1,4,0,task);
        work->timer=20;
        event->phase++;
        break;
    case 257: {
        struct ActorSetupEvent child_event;
        work->timer--;
        if(work->timer!=0) break;
        if((u8)CountActorSetupTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        child_event.definition=101;
        child_event.variant=1;
        child_event.record=work->record;
        work->child=CreateActorSetupTask(ActorSetupChild,28,&child_event,task);
        event->phase++;
        break;
    }
    case 258:
        work->projected=PollActorSetupProjected(work->projected);
        if(work->projected!=0) break;
        work->child=PollActorSetupChild(work->child);
        if(work->child!=0) break;
        event->phase=2;
        break;
    }
    return 0;
}

__asm__(".global CreateActorSetupInitial\n.thumb_set CreateActorSetupInitial,0x080e03f9");
__asm__(".global CleanupActorSetupInputs\n.thumb_set CleanupActorSetupInputs,0x080d38b5");
__asm__(".global PollActorSetupInitial\n.thumb_set PollActorSetupInitial,0x080e05dd");
__asm__(".global IsActorSetupUnavailable\n.thumb_set IsActorSetupUnavailable,0x080d3b55");
__asm__(".global GetActorSetupActor\n.thumb_set GetActorSetupActor,0x080dd47d");
__asm__(".global SetActorSetupParameter\n.thumb_set SetActorSetupParameter,0x080de10d");
__asm__(".global SetActorSetupPhase\n.thumb_set SetActorSetupPhase,0x080de3bd");
__asm__(".global ProjectActorSetupPosition\n.thumb_set ProjectActorSetupPosition,0x080dbdc9");
__asm__(".global CreateActorSetupProjected\n.thumb_set CreateActorSetupProjected,0x080d6099");
__asm__(".global CreateActorSetupStage\n.thumb_set CreateActorSetupStage,0x080dfd8d");
__asm__(".global CountActorSetupTargets\n.thumb_set CountActorSetupTargets,0x080d8859");
__asm__(".global ActorSetupChild\n.thumb_set ActorSetupChild,0x080e4055");
__asm__(".global CreateActorSetupTask\n.thumb_set CreateActorSetupTask,0x08005b6d");
__asm__(".global PollActorSetupProjected\n.thumb_set PollActorSetupProjected,0x080d6135");
__asm__(".global PollActorSetupChild\n.thumb_set PollActorSetupChild,0x080e051d");
__asm__(".balign 4,0");
