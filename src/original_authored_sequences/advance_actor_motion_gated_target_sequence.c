typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct MotionGateEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct MotionGateWork {
    s16 x,y;
    u8 variant,ready,trigger;
    s8 count;
    u8 delay,unknown09;
    u16 phase_counter;
    TaskNode *filter,*children[4];
    void *actor;
    TaskNode *sequences[2],*timed;
    void *record;
    TaskNode *initial,*motion,*actor_sequence,*stage;
};
typedef char MotionGateEventMustBe28[sizeof(struct MotionGateEvent)==28?1:-1];
typedef char MotionGateWorkMustBe68[sizeof(struct MotionGateWork)==68?1:-1];
extern TaskNode *CreateMotionGateInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupMotionGateInputs(void);
extern TaskNode *PollMotionGateInitial(TaskNode *);
extern u32 CountMotionGateDirectTargets(void *);
extern TaskNode *CreateMotionGateActorSequence(void *,void **,u16,u8,u8 *,const void *,u8,u8,TaskNode *);
extern void ProjectMotionGateActor(void *,s16 *,s16 *);
extern TaskNode *CreateMotionGateActorMotion(void *,u16,u16,u16,TaskNode *);
extern TaskNode *PollMotionGateMotion(TaskNode *);
extern void CreateMotionGatePositionedSequence(const void *,u32,u32,s32,s32,u32);
extern TaskNode *CreateMotionGateSequence(const void *,TaskNode *);
extern TaskNode *CreateMotionGateTimedSequence(const void *,TaskNode *,u16);
extern TaskNode *CreateMotionGateFilter(const void *,TaskNode *);
extern TaskNode *CreateMotionGateStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollMotionGateSequence(TaskNode *);
extern u32 CountMotionGateEligibleTargets(void *,u8);
extern u32 PollMotionGateChildren(TaskNode **,u32);
extern void *GetMotionGateTarget(void *,u8);
extern u32 MotionGateTargetChild(TaskNode *,struct MotionGateEvent *,void *);
extern TaskNode *CreateMotionGateTask(u32 (*)(TaskNode *,struct MotionGateEvent *,void *),u32,struct MotionGateEvent *,TaskNode *);
extern u32 IsMotionGateActorFinished(void *);
extern TaskNode *PollMotionGateFilter(TaskNode *);
extern u32 MotionGateControlMask(u8);
extern u16 MotionGateDisplayFlags;
extern u32 PollMotionGateSequences(TaskNode **,u32);

u32 AdvanceActorMotionGatedTargetSequence(TaskNode *,struct MotionGateEvent *,struct MotionGateWork *)
    __asm__("OriginalActionCallback_000F9168");
u32 AdvanceActorMotionGatedTargetSequence(TaskNode *task,struct MotionGateEvent *event,
                                        struct MotionGateWork *work)
{
    u32 mask;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=4;
        if(work->variant!=0) count=0;
        work->initial=CreateMotionGateInitial(work->record,(const void *)0x0839C3E0,count,0,0,task);
        break;
    }
    case 1:
        CleanupMotionGateInputs();
        break;
    case 256:
        work->initial=PollMotionGateInitial(work->initial);
        if(work->initial!=0) break;
        if(work->variant!=0) {
            work->count=CountMotionGateDirectTargets(work->record);
            work->delay=1;
            event->phase=260;
            break;
        }
        work->actor_sequence=CreateMotionGateActorSequence(work->record,&work->actor,152,2,
                                 &work->ready,(const void *)0x0839C43C,0,0,task);
        ProjectMotionGateActor(work->actor,&work->x,&work->y);
        event->phase++;
        break;
    case 257:
        if(work->ready==0) break;
        work->motion=CreateMotionGateActorMotion(work->actor,8,12,0,task);
        event->phase++;
        break;
    case 258: {
        TaskNode *motion;
        motion=PollMotionGateMotion(work->motion);
        work->motion=motion;
        if(motion!=0) break;
        if(work->trigger==0) break;
        CreateMotionGatePositionedSequence((const void *)0x088F58BC,0,2,work->x,work->y,(u32)motion);
        work->sequences[0]=CreateMotionGateSequence((const void *)0x08949AFC,task);
        work->sequences[1]=CreateMotionGateSequence((const void *)0x08949CB8,task);
        work->timed=CreateMotionGateTimedSequence((const void *)0x0894ABF0,task,20);
        work->filter=CreateMotionGateFilter((const void *)0x0894D690,task);
        work->stage=CreateMotionGateStage((const void *)0x0839C444,1,4,0,task);
        work->phase_counter=60;
        event->phase++;
        break;
    }
    case 259: {
        u32 raw_counter,raw_count;
        raw_counter=(u32)work->phase_counter-1;
        work->phase_counter=raw_counter;
        if((u16)raw_counter!=0) break;
        work->timed=PollMotionGateSequence(work->timed);
        if(work->timed!=0) break;
        raw_count=CountMotionGateEligibleTargets(work->record,0);
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
        struct MotionGateEvent child_event;
        TaskNode **children;
        TaskNode *child;
        u32 raw_delay;
        children=&work->children[0];
        PollMotionGateChildren(children,4);
        raw_delay=(u32)work->delay-1;
        work->delay=raw_delay;
        if((u8)raw_delay!=0) break;
        child_event.definition=work->phase_counter;
        child_event.record=GetMotionGateTarget(work->record,(u8)work->phase_counter);
        child=CreateMotionGateTask(MotionGateTargetChild,32,&child_event,task);
        *(TaskNode **)((u32)children+((u32)work->phase_counter<<2))=child;
        work->delay=30;
        work->phase_counter++;
        if(work->phase_counter==work->count) event->phase++;
        break;
    }
    case 261:
        if((u8)IsMotionGateActorFinished(work->actor)==0) break;
        work->filter=PollMotionGateFilter(work->filter);
        if(work->filter!=0) break;
        mask=MotionGateControlMask(2);
        MotionGateDisplayFlags&=~mask;
        if((u8)PollMotionGateSequences(&work->sequences[0],2)==0) break;
        if((u8)PollMotionGateChildren(&work->children[0],4)!=0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateMotionGateInitial\n.thumb_set CreateMotionGateInitial,0x80e03f9");
__asm__(".global CleanupMotionGateInputs\n.thumb_set CleanupMotionGateInputs,0x80d38b5");
__asm__(".global PollMotionGateInitial\n.thumb_set PollMotionGateInitial,0x80e05dd");
__asm__(".global CountMotionGateDirectTargets\n.thumb_set CountMotionGateDirectTargets,0x80dd495");
__asm__(".global CreateMotionGateActorSequence\n.thumb_set CreateMotionGateActorSequence,0x80ddf69");
__asm__(".global ProjectMotionGateActor\n.thumb_set ProjectMotionGateActor,0x80dbdc9");
__asm__(".global CreateMotionGateActorMotion\n.thumb_set CreateMotionGateActorMotion,0x80dbb15");
__asm__(".global PollMotionGateMotion\n.thumb_set PollMotionGateMotion,0x80dba5d");
__asm__(".global CreateMotionGatePositionedSequence\n.thumb_set CreateMotionGatePositionedSequence,0x80d7221");
__asm__(".global CreateMotionGateSequence\n.thumb_set CreateMotionGateSequence,0x80d4705");
__asm__(".global CreateMotionGateTimedSequence\n.thumb_set CreateMotionGateTimedSequence,0x80d4725");
__asm__(".global CreateMotionGateFilter\n.thumb_set CreateMotionGateFilter,0x80d3e9d");
__asm__(".global CreateMotionGateStage\n.thumb_set CreateMotionGateStage,0x80dfd8d");
__asm__(".global PollMotionGateSequence\n.thumb_set PollMotionGateSequence,0x80d4775");
__asm__(".global CountMotionGateEligibleTargets\n.thumb_set CountMotionGateEligibleTargets,0x80d8859");
__asm__(".global PollMotionGateChildren\n.thumb_set PollMotionGateChildren,0x80e0571");
__asm__(".global GetMotionGateTarget\n.thumb_set GetMotionGateTarget,0x80dd4a5");
__asm__(".global MotionGateTargetChild\n.thumb_set MotionGateTargetChild,0x80f9095");
__asm__(".global CreateMotionGateTask\n.thumb_set CreateMotionGateTask,0x8005b6d");
__asm__(".global IsMotionGateActorFinished\n.thumb_set IsMotionGateActorFinished,0x80de1f1");
__asm__(".global PollMotionGateFilter\n.thumb_set PollMotionGateFilter,0x80d3f09");
__asm__(".global MotionGateControlMask\n.thumb_set MotionGateControlMask,0x80035a9");
__asm__(".global PollMotionGateSequences\n.thumb_set PollMotionGateSequences,0x80d48dd");
__asm__(".global MotionGateDisplayFlags\n.set MotionGateDisplayFlags,0x03000940");
