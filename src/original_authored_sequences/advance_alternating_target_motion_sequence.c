typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct AlternatingActionEvent {
    u16 phase;
    u8 unknown02[2];
    void *argument, *record;
    u8 unknown0C[8];
    u16 parameter, ordinal;
    u8 unknown18[4];
};
struct AlternatingActionWork {
    s16 x, y;
    u8 variant, complete, unknown06, target_count;
    u8 ordinal, delay;
    u16 timer;
    void *resources[2];
    TaskNode *projected, *sequence, *children[4];
    void *actor, *record;
    TaskNode *initial, *actor_sequence, *motions[4], *stage;
};
typedef char AlternatingEventMustBe28[sizeof(struct AlternatingActionEvent)==28?1:-1];
typedef char AlternatingWorkMustBe80[sizeof(struct AlternatingActionWork)==80?1:-1];
extern TaskNode *CreateAlternatingInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupAlternatingInputs(void);
extern TaskNode *PollAlternatingInitial(TaskNode *);
extern u32 CountAlternatingRecordEntries(void *);
extern TaskNode *CreateAlternatingActorSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern void ProjectAlternatingActor(void *,s16 *,s16 *);
extern TaskNode *CreateAlternatingProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateAlternatingStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollAlternatingProjected(TaskNode *);
extern void SetAlternatingActorPhase(void *,u8);
extern void CancelAlternatingActorSequence(TaskNode *);
extern TaskNode *ReplaceAlternatingActorSequence(void *,u8,u8 *,const void *,u32,u32,TaskNode *);
extern TaskNode *CreateAlternatingSequence(const void *,TaskNode *,u16);
extern u32 CountAlternatingTargets(void *,u8);
extern void *GetAlternatingTarget(void *,u8);
extern u32 AlternatingTargetChild(TaskNode *,struct AlternatingActionEvent *,void *);
extern TaskNode *CreateAlternatingTask(u32 (*)(TaskNode *,struct AlternatingActionEvent *,void *),u32,struct AlternatingActionEvent *,TaskNode *);
extern u32 PollAlternatingChildren(TaskNode **,u8);
extern TaskNode *PollAlternatingSequence(TaskNode *);
extern void TouchAlternatingTarget(void *,u8);
extern u32 IsAlternatingActionBusy(void);
extern TaskNode *CreateAlternatingMotion(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern u32 IsAlternatingActorFinished(void *);
extern TaskNode *PollAlternatingMotion(TaskNode *);

u32 AdvanceAlternatingTargetMotionSequence(TaskNode *,struct AlternatingActionEvent *,struct AlternatingActionWork *)
    __asm__("OriginalActionCallback_000F5864");
u32 AdvanceAlternatingTargetMotionSequence(TaskNode *task,struct AlternatingActionEvent *event,
                                         struct AlternatingActionWork *work)
{
    struct AlternatingActionEvent child_event;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->ordinal;
        work->record=event->argument;
        count=5;
        if(work->variant!=0) count=0;
        work->initial=CreateAlternatingInitial(work->record,(const void *)0x0839B418,count,0,0,task);
        break;
    }
    case 1:
        CleanupAlternatingInputs();
        break;
    case 256: {
        u8 variant;
        work->initial=PollAlternatingInitial(work->initial);
        if(work->initial!=0) break;
        variant=work->variant;
        if(variant!=0) {
            work->target_count=CountAlternatingRecordEntries(work->record);
            work->delay=1;
            event->phase=261;
            break;
        }
        work->actor_sequence=CreateAlternatingActorSequence(work->record,&work->actor,144,1,
                                                            &work->complete,(const void *)0x0839B4B0,
                                                            variant,variant,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->complete==0) break;
        ProjectAlternatingActor(work->actor,&work->x,&work->y);
        work->projected=CreateAlternatingProjected(work->x,work->y,0,1,1,
                                                   work->resources,(const void *)0x0839B454,task);
        work->stage=CreateAlternatingStage((const void *)0x0839B4B8,1,4,0,task);
        event->phase++;
        break;
    case 258: {
        TaskNode *projected;
        projected=PollAlternatingProjected(work->projected);
        work->projected=projected;
        if(projected!=0) break;
        SetAlternatingActorPhase(work->actor,0);
        CancelAlternatingActorSequence(work->actor_sequence);
        work->actor_sequence=ReplaceAlternatingActorSequence(work->actor,1,&work->complete,
                                                             (const void *)0x0839B4B4,
                                                             (u32)projected,(u32)projected,task);
        event->phase++;
        break;
    }
    case 259:
        if(work->complete==0) break;
        work->projected=CreateAlternatingProjected(work->x,work->y,0,1,2,
                                                   work->resources,(const void *)0x0839B46C,task);
        work->stage=CreateAlternatingStage((const void *)0x0839B4C0,1,4,0,task);
        CancelAlternatingActorSequence(work->actor_sequence);
        work->sequence=CreateAlternatingSequence((const void *)0x0894AD30,task,10);
        work->timer=20;
        event->phase++;
        break;
    case 260: {
        u16 ordinal;
        u8 index;
        work->timer--;
        if(work->timer!=0) break;
        work->target_count=CountAlternatingTargets(work->record,0);
        if(work->target_count==0) {
            event->phase=2;
            break;
        }
        ordinal=0;
        index=0;
        while(index<work->target_count) {
            TaskNode *child;
            TaskNode **destination;
            u32 byte_offset;
            child_event.parameter=index;
            child_event.ordinal=ordinal;
            child_event.argument=GetAlternatingTarget(work->record,index);
            child_event.record=work->record;
            child=CreateAlternatingTask(AlternatingTargetChild,28,&child_event,task);
            byte_offset=(u32)index<<2;
            destination=(TaskNode **)((u8 *)work+28);
            destination=(TaskNode **)((u8 *)destination+byte_offset);
            *destination=child;
            ordinal++;
            index++;
        }
        event->phase++;
        break;
    }
    case 261:
        if((u8)PollAlternatingChildren(work->children,4)==0) break;
        work->sequence=PollAlternatingSequence(work->sequence);
        if(work->sequence!=0) break;
        work->delay=1;
        event->phase++;
        break;
    case 262:
        TouchAlternatingTarget(work->record,work->ordinal);
        event->phase++;
        /* The original enters the next polling stage in this same call. */
    case 263: {
        u32 delay;
        register u32 raw_delay __asm__("r0");
        void *cell;
        u32 parity, flags, byte_offset;
        TaskNode *motion;
        TaskNode **destination;
        if((u8)IsAlternatingActionBusy()!=0) break;
        raw_delay=(u32)work->delay-1;
        work->delay=raw_delay;
        /* Publish the byte before capturing the complete LOW8 call value. */
        __asm__("" : "+r"(raw_delay));
        delay=(u8)raw_delay;
        if(delay!=0) break;
        cell=GetAlternatingTarget(work->record,work->ordinal);
        parity=work->ordinal&1;
        flags=2;
        if(parity!=0) flags=4;
        motion=CreateAlternatingMotion(cell,(const void *)0x0839B49C,(u8)(12-parity),0,
                                        flags|8,task,delay);
        byte_offset=(u32)work->ordinal<<2;
        destination=(TaskNode **)((u8 *)work+60);
        destination=(TaskNode **)((u8 *)destination+byte_offset);
        *destination=motion;
        work->delay=40;
        work->ordinal++;
        if(work->ordinal!=work->target_count) {
            event->phase=262;
            break;
        }
        event->phase++;
        break;
    }
    case 264: {
        u8 index, all_done;
        if((u8)IsAlternatingActorFinished(work->actor)==0) break;
        all_done=1;
        for(index=0;index<=3;index++) {
            work->motions[index]=PollAlternatingMotion(work->motions[index]);
            if(work->motions[index]!=0) all_done=0;
        }
        if(all_done!=0) event->phase=2;
        break;
    }
    }
    return 0;
}

__asm__(".global CreateAlternatingInitial\n.thumb_set CreateAlternatingInitial,0x080e03f9");
__asm__(".global CleanupAlternatingInputs\n.thumb_set CleanupAlternatingInputs,0x080d38b5");
__asm__(".global PollAlternatingInitial\n.thumb_set PollAlternatingInitial,0x080e05dd");
__asm__(".global CountAlternatingRecordEntries\n.thumb_set CountAlternatingRecordEntries,0x080dd495");
__asm__(".global CreateAlternatingActorSequence\n.thumb_set CreateAlternatingActorSequence,0x080ddf69");
__asm__(".global ProjectAlternatingActor\n.thumb_set ProjectAlternatingActor,0x080dbdc9");
__asm__(".global CreateAlternatingProjected\n.thumb_set CreateAlternatingProjected,0x080d6099");
__asm__(".global CreateAlternatingStage\n.thumb_set CreateAlternatingStage,0x080dfd8d");
__asm__(".global PollAlternatingProjected\n.thumb_set PollAlternatingProjected,0x080d6135");
__asm__(".global SetAlternatingActorPhase\n.thumb_set SetAlternatingActorPhase,0x080de3bd");
__asm__(".global CancelAlternatingActorSequence\n.thumb_set CancelAlternatingActorSequence,0x080dba51");
__asm__(".global ReplaceAlternatingActorSequence\n.thumb_set ReplaceAlternatingActorSequence,0x080de4f5");
__asm__(".global CreateAlternatingSequence\n.thumb_set CreateAlternatingSequence,0x080d4725");
__asm__(".global CountAlternatingTargets\n.thumb_set CountAlternatingTargets,0x080d8859");
__asm__(".global GetAlternatingTarget\n.thumb_set GetAlternatingTarget,0x080dd4a5");
__asm__(".global AlternatingTargetChild\n.thumb_set AlternatingTargetChild,0x080f5711");
__asm__(".global CreateAlternatingTask\n.thumb_set CreateAlternatingTask,0x08005b6d");
__asm__(".global PollAlternatingChildren\n.thumb_set PollAlternatingChildren,0x080e0571");
__asm__(".global PollAlternatingSequence\n.thumb_set PollAlternatingSequence,0x080d4775");
__asm__(".global TouchAlternatingTarget\n.thumb_set TouchAlternatingTarget,0x080dbffd");
__asm__(".global IsAlternatingActionBusy\n.thumb_set IsAlternatingActionBusy,0x080d8b4d");
__asm__(".global CreateAlternatingMotion\n.thumb_set CreateAlternatingMotion,0x080dcfe5");
__asm__(".global IsAlternatingActorFinished\n.thumb_set IsAlternatingActorFinished,0x080de1f1");
__asm__(".global PollAlternatingMotion\n.thumb_set PollAlternatingMotion,0x080dba5d");
__asm__(".balign 4,0");
