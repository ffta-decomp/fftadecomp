typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct CadencedEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct CadencedWork {
    s16 x,y;
    u8 unknown04,variant,ready,unknown07;
    s8 count;
    u8 delay;
    u16 phase_counter;
    u8 resources[12];
    void *projected;
    TaskNode *filter,*children[4];
    void *actor;
    TaskNode *sequence_a,*sequence_b;
    void *record;
    TaskNode *initial,*actor_sequence,*stage;
};
typedef char CadencedEventMustBe28[sizeof(struct CadencedEvent)==28?1:-1];
typedef char CadencedWorkMustBe76[sizeof(struct CadencedWork)==76?1:-1];
extern TaskNode *CreateCadencedInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupCadencedInputs(void);
extern TaskNode *PollCadencedInitial(TaskNode *);
extern u32 CountCadencedDirectTargets(void *);
extern TaskNode *CreateCadencedActorSequence(void *,void **,u16,u8,u8 *,const void *,u8,u8,TaskNode *);
extern void ProjectCadencedActor(void *,s16 *,s16 *);
extern void *CreateCadencedProjected(s32,s32,u32,u32,u32,void *,const void *,TaskNode *);
extern u32 GetCadencedActorMode(void *);
extern void SetCadencedProjectedOption(void *,u8);
extern TaskNode *CreateCadencedStage(const void *,u8,u16,u16,TaskNode *);
extern void CreateCadencedPositionedSequence(const void *,u32,u32,s32,s32,u16);
extern TaskNode *CreateCadencedSequence(const void *,TaskNode *);
extern TaskNode *CreateCadencedFilter(const void *,TaskNode *);
extern u32 IsCadencedActorFinished(void *);
extern u32 CountCadencedEligibleTargets(void *,u8);
extern u32 PollCadencedChildren(TaskNode **,u32);
extern void *GetCadencedTarget(void *,u8);
extern u32 CadencedTargetChild(TaskNode *,struct CadencedEvent *,void *);
extern TaskNode *CreateCadencedTask(u32 (*)(TaskNode *,struct CadencedEvent *,void *),u32,struct CadencedEvent *,TaskNode *);
extern void *PollCadencedProjected(void *);
extern TaskNode *PollCadencedFilter(TaskNode *);
extern u32 CadencedControlMask(u8);
extern u16 CadencedDisplayFlags;
extern TaskNode *PollCadencedSequence(TaskNode *);

u32 AdvancePositionedCadencedTargetSequence(TaskNode *,struct CadencedEvent *,struct CadencedWork *)
    __asm__("OriginalActionCallback_000F86EC");
u32 AdvancePositionedCadencedTargetSequence(TaskNode *task,struct CadencedEvent *event,
                                          struct CadencedWork *work)
{
    u32 mask;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=6;
        if(work->variant!=0) count=0;
        work->initial=CreateCadencedInitial(work->record,(const void *)0x0839C030,count,0,0,task);
        break;
    }
    case 1:
        CleanupCadencedInputs();
        break;
    case 256:
        work->initial=PollCadencedInitial(work->initial);
        if(work->initial!=0) break;
        if(work->variant!=0) {
            work->count=CountCadencedDirectTargets(work->record);
            work->delay=1;
            event->phase=260;
            break;
        }
        work->actor_sequence=CreateCadencedActorSequence(work->record,&work->actor,148,1,
                                   &work->ready,(const void *)0x0839C104,0,0,task);
        ProjectCadencedActor(work->actor,&work->x,&work->y);
        event->phase++;
        break;
    case 257:
        if(work->ready==0) break;
        work->projected=CreateCadencedProjected(work->x,work->y,0,1,3,&work->resources[0],
                                                (const void *)0x0839C078,task);
        if((s8)GetCadencedActorMode(work->actor)>1)
            SetCadencedProjectedOption(work->projected,1);
        work->stage=CreateCadencedStage((const void *)0x0839C108,2,4,0,task);
        work->phase_counter=21;
        event->phase++;
        break;
    case 258: {
        u32 raw_counter;
        u16 remaining;
        raw_counter=(u32)work->phase_counter-1;
        work->phase_counter=raw_counter;
        remaining=raw_counter;
        if(remaining!=0) break;
        CreateCadencedPositionedSequence((const void *)0x088F58BC,0,2,work->x,work->y,remaining);
        work->sequence_a=CreateCadencedSequence((const void *)0x0894A130,task);
        work->sequence_b=CreateCadencedSequence((const void *)0x0894ABF0,task);
        work->filter=CreateCadencedFilter((const void *)0x0894D92C,task);
        event->phase++;
        break;
    }
    case 259: {
        u32 raw_count;
        if((u8)IsCadencedActorFinished(work->actor)==0) break;
        raw_count=CountCadencedEligibleTargets(work->record,0);
        work->count=raw_count;
        if((s8)raw_count<=0) {
            event->phase=261;
            break;
        }
        work->delay=1;
        event->phase++;
        break;
    }
    case 260: {
        struct CadencedEvent child_event;
        TaskNode **children;
        TaskNode *child;
        u32 raw_delay;
        children=&work->children[0];
        PollCadencedChildren(children,4);
        raw_delay=(u32)work->delay-1;
        work->delay=raw_delay;
        if((u8)raw_delay!=0) break;
        child_event.definition=work->phase_counter;
        child_event.record=GetCadencedTarget(work->record,(u8)work->phase_counter);
        child=CreateCadencedTask(CadencedTargetChild,36,&child_event,task);
        *(TaskNode **)((u32)children+((u32)work->phase_counter<<2))=child;
        work->delay=30;
        work->phase_counter++;
        if(work->phase_counter==work->count) event->phase++;
        break;
    }
    case 261:
        work->projected=PollCadencedProjected(work->projected);
        if(work->projected!=0) break;
        work->filter=PollCadencedFilter(work->filter);
        if(work->filter!=0) break;
        mask=CadencedControlMask(2);
        CadencedDisplayFlags&=~mask;
        work->sequence_a=PollCadencedSequence(work->sequence_a);
        if(work->sequence_a!=0) break;
        work->sequence_b=PollCadencedSequence(work->sequence_b);
        if(work->sequence_b!=0) break;
        if((u8)PollCadencedChildren(&work->children[0],4)!=0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateCadencedInitial\n.thumb_set CreateCadencedInitial,0x80e03f9");
__asm__(".global CleanupCadencedInputs\n.thumb_set CleanupCadencedInputs,0x80d38b5");
__asm__(".global PollCadencedInitial\n.thumb_set PollCadencedInitial,0x80e05dd");
__asm__(".global CountCadencedDirectTargets\n.thumb_set CountCadencedDirectTargets,0x80dd495");
__asm__(".global CreateCadencedActorSequence\n.thumb_set CreateCadencedActorSequence,0x80ddf69");
__asm__(".global ProjectCadencedActor\n.thumb_set ProjectCadencedActor,0x80dbdc9");
__asm__(".global CreateCadencedProjected\n.thumb_set CreateCadencedProjected,0x80d6099");
__asm__(".global GetCadencedActorMode\n.thumb_set GetCadencedActorMode,0x80dbc89");
__asm__(".global SetCadencedProjectedOption\n.thumb_set SetCadencedProjectedOption,0x80d6195");
__asm__(".global CreateCadencedStage\n.thumb_set CreateCadencedStage,0x80dfd8d");
__asm__(".global CreateCadencedPositionedSequence\n.thumb_set CreateCadencedPositionedSequence,0x80d7221");
__asm__(".global CreateCadencedSequence\n.thumb_set CreateCadencedSequence,0x80d4705");
__asm__(".global CreateCadencedFilter\n.thumb_set CreateCadencedFilter,0x80d3e9d");
__asm__(".global IsCadencedActorFinished\n.thumb_set IsCadencedActorFinished,0x80de1f1");
__asm__(".global CountCadencedEligibleTargets\n.thumb_set CountCadencedEligibleTargets,0x80d8859");
__asm__(".global PollCadencedChildren\n.thumb_set PollCadencedChildren,0x80e0571");
__asm__(".global GetCadencedTarget\n.thumb_set GetCadencedTarget,0x80dd4a5");
__asm__(".global CadencedTargetChild\n.thumb_set CadencedTargetChild,0x80f8609");
__asm__(".global CreateCadencedTask\n.thumb_set CreateCadencedTask,0x8005b6d");
__asm__(".global PollCadencedProjected\n.thumb_set PollCadencedProjected,0x80d6135");
__asm__(".global PollCadencedFilter\n.thumb_set PollCadencedFilter,0x80d3f09");
__asm__(".global CadencedControlMask\n.thumb_set CadencedControlMask,0x80035a9");
__asm__(".global PollCadencedSequence\n.thumb_set PollCadencedSequence,0x80d4775");
__asm__(".global CadencedDisplayFlags\n.set CadencedDisplayFlags,0x03000940");
