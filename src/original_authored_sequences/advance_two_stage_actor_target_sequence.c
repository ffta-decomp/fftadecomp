typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct TwoStageActionEvent {
    u16 phase;
    u8 unknown02[2];
    void *record;
    u8 unknown08[12];
    u16 ordinal, variant;
    u8 unknown18[4];
};
struct TwoStageActionWork {
    s16 x, y;
    u8 unknown04, variant, complete, unknown07;
    s8 last_target;
    u8 delay;
    u16 timer_ordinal;
    void *resources[3];
    TaskNode *projected, *display_effect, *sequence, *children[4];
    void *actor;
    TaskNode *timed_sequence;
    void *record;
    TaskNode *initial, *actor_sequence, *motion, *stage;
};
typedef char TwoStageEventMustBe28[sizeof(struct TwoStageActionEvent)==28?1:-1];
typedef char TwoStageWorkMustBe80[sizeof(struct TwoStageActionWork)==80?1:-1];
extern u16 TwoStageDisplayFlags;
extern TaskNode *CreateTwoStageInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupTwoStageInputs(void);
extern TaskNode *PollTwoStageInitial(TaskNode *);
extern void *GetTwoStageActor(void *);
extern void ProjectTwoStageActor(void *,s16 *,s16 *);
extern u32 CountTwoStageRecordEntries(void *);
extern void SetTwoStageActorParameter(void *,u8);
extern void PositionTwoStageDisplay(u8,u8,u8,s32,s32);
extern TaskNode *CreateTwoStageDisplayEffect(u8,const void *,u16,u8);
extern u32 TwoStageDisplayFlagMask(u8);
extern TaskNode *CreateTwoStageSequence(const void *,TaskNode *);
extern TaskNode *CreateTwoStageProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateTwoStageStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollTwoStageDisplayEffect(TaskNode *,u8);
extern TaskNode *PollTwoStageSequence(TaskNode *);
extern TaskNode *CreateTwoStageActorSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern u32 GetTwoStageActorSelector(void *);
extern void SetTwoStageProjectedOption(TaskNode *,u8);
extern void SetTwoStageSequenceOption(TaskNode *,u8,u8);
extern TaskNode *CreateTwoStageTimedSequence(const void *,TaskNode *,u16);
extern TaskNode *PollTwoStageProjected(TaskNode *);
extern TaskNode *PollTwoStageTimedSequence(TaskNode *);
extern u32 IsTwoStageActorFinished(void *);
extern u32 AuthorizeTwoStageTargets(void *,u8,u16,TaskNode *);
extern u32 PollTwoStageChildren(TaskNode **,u8);
extern void *GetTwoStageTarget(void *,u8);
extern u32 TwoStageTargetChild(TaskNode *,struct TwoStageActionEvent *,void *);
extern TaskNode *CreateTwoStageTask(u32 (*)(TaskNode *,struct TwoStageActionEvent *,void *),u32,struct TwoStageActionEvent *,TaskNode *);
extern TaskNode *CreateTwoStageMotion(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern TaskNode *PollTwoStageMotion(TaskNode *);

u32 AdvanceTwoStageActorTargetSequence(TaskNode *,struct TwoStageActionEvent *,struct TwoStageActionWork *)
    __asm__("OriginalActionCallback_000F6060");
u32 AdvanceTwoStageActorTargetSequence(TaskNode *task,struct TwoStageActionEvent *event,
                                     struct TwoStageActionWork *work)
{
    struct TwoStageActionEvent child_event;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=8;
        if(work->variant!=0) count=0;
        work->initial=CreateTwoStageInitial(work->record,(const void *)0x0839B664,count,0,0,task);
        break;
    }
    case 1:
        CleanupTwoStageInputs();
        break;
    case 256:
        work->initial=PollTwoStageInitial(work->initial);
        if(work->initial!=0) break;
        work->actor=GetTwoStageActor(work->record);
        ProjectTwoStageActor(work->actor,&work->x,&work->y);
        if(work->variant!=0) {
            work->last_target=CountTwoStageRecordEntries(work->record)-1;
            work->delay=1;
            event->phase=261;
            break;
        }
        SetTwoStageActorParameter(work->actor,36);
        PositionTwoStageDisplay(0,2,0,work->x,work->y);
        work->display_effect=CreateTwoStageDisplayEffect(0,(const void *)0x088EF398,959,6);
        {
            u32 mask;
            register u32 control __asm__("r1");
            mask=TwoStageDisplayFlagMask(2);
            control=TwoStageDisplayFlags;
            /* Original OR destructively updates this freshly read halfword. */
            __asm__("" : "+r"(control));
            control|=mask;
            TwoStageDisplayFlags=control;
        }
        work->sequence=CreateTwoStageSequence((const void *)0x0894D90C,task);
        work->projected=CreateTwoStageProjected(work->x,work->y,0,1,1,
                                    work->resources,(const void *)0x0839B6C4,task);
        work->stage=CreateTwoStageStage((const void *)0x0839B798,1,4,0,task);
        event->phase++;
        break;
    case 257: {
        TaskNode *sequence;
        work->display_effect=PollTwoStageDisplayEffect(work->display_effect,0);
        if(work->display_effect!=0) break;
        sequence=PollTwoStageSequence(work->sequence);
        work->sequence=sequence;
        if(sequence!=0) break;
        {
            u32 mask;
            mask=TwoStageDisplayFlagMask(2);
            TwoStageDisplayFlags&=~mask;
        }
        /* Both zero arguments are the actual full-width completed handle. */
        work->actor_sequence=CreateTwoStageActorSequence(work->record,&work->actor,148,1,
                                      &work->complete,(const void *)0x0839B794,
                                      (u32)sequence,(u32)sequence,task);
        event->phase++;
        break;
    }
    case 258:
        if(work->complete==0) break;
        work->projected=CreateTwoStageProjected(work->x,work->y,0,1,3,
                                    work->resources,(const void *)0x0839B6DC,task);
        if((s8)GetTwoStageActorSelector(work->actor)>1)
            SetTwoStageProjectedOption(work->projected,1);
        work->timer_ordinal=4;
        event->phase++;
        break;
    case 259:
        work->timer_ordinal--;
        if(work->timer_ordinal!=0) break;
        PositionTwoStageDisplay(1,3,0,work->x,work->y);
        work->display_effect=CreateTwoStageDisplayEffect(1,(const void *)0x088EF44C,861,7);
        {
            u32 mask;
            register u32 control __asm__("r1");
            mask=TwoStageDisplayFlagMask(3);
            control=TwoStageDisplayFlags;
            /* Original OR destructively updates this freshly read halfword. */
            __asm__("" : "+r"(control));
            control|=mask;
            TwoStageDisplayFlags=control;
        }
        work->sequence=CreateTwoStageSequence((const void *)0x0894D91C,task);
        SetTwoStageSequenceOption(work->sequence,8,255);
        work->timed_sequence=CreateTwoStageTimedSequence((const void *)0x089484DC,task,30);
        work->stage=CreateTwoStageStage((const void *)0x0839B7A0,1,4,0,task);
        event->phase++;
        break;
    case 260:
        work->projected=PollTwoStageProjected(work->projected);
        if(work->projected!=0) break;
        work->display_effect=PollTwoStageDisplayEffect(work->display_effect,1);
        if(work->display_effect!=0) break;
        work->sequence=PollTwoStageSequence(work->sequence);
        if(work->sequence!=0) break;
        {
            u32 mask;
            mask=TwoStageDisplayFlagMask(3);
            TwoStageDisplayFlags&=~mask;
        }
        work->timed_sequence=PollTwoStageTimedSequence(work->timed_sequence);
        if(work->timed_sequence!=0) break;
        if((u8)IsTwoStageActorFinished(work->actor)==0) break;
        work->last_target=AuthorizeTwoStageTargets(work->record,0,56,task)-1;
        if(work->last_target<=0) {
            event->phase=262;
            break;
        }
        work->delay=1;
        event->phase++;
        break;
    case 261: {
        TaskNode **children;
        TaskNode *child;
        TaskNode **destination;
        u32 byte_offset;
        children=work->children;
        PollTwoStageChildren(children,4);
        work->delay--;
        if(work->delay!=0) break;
        child_event.ordinal=work->timer_ordinal;
        child_event.record=GetTwoStageTarget(work->record,(u8)work->timer_ordinal);
        child=CreateTwoStageTask(TwoStageTargetChild,36,&child_event,task);
        byte_offset=(u32)work->timer_ordinal<<2;
        destination=(TaskNode **)((u8 *)children+byte_offset);
        *destination=child;
        work->delay=30;
        work->timer_ordinal++;
        if(work->timer_ordinal==work->last_target) event->phase++;
        break;
    }
    case 262:
        if((u8)PollTwoStageChildren(work->children,4)!=0) event->phase++;
        break;
    case 263: {
        void *target;
        work->projected=CreateTwoStageProjected(work->x,work->y,0,1,1,
                                    work->resources,(const void *)0x0839B754,task);
        work->stage=CreateTwoStageStage((const void *)0x0839B7A8,1,4,0,task);
        target=GetTwoStageTarget(work->record,(u8)work->last_target);
        work->motion=CreateTwoStageMotion(target,(const void *)0x0839B780,12,40,16,task,40);
        event->phase++;
        break;
    }
    case 264:
        work->projected=PollTwoStageProjected(work->projected);
        if(work->projected!=0) break;
        work->motion=PollTwoStageMotion(work->motion);
        if(work->motion!=0) break;
        event->phase=2;
        break;
    }
    return 0;
}

__asm__(".global TwoStageDisplayFlags\n.set TwoStageDisplayFlags,0x03000940");
__asm__(".global CreateTwoStageInitial\n.thumb_set CreateTwoStageInitial,0x080e03f9");
__asm__(".global CleanupTwoStageInputs\n.thumb_set CleanupTwoStageInputs,0x080d38b5");
__asm__(".global PollTwoStageInitial\n.thumb_set PollTwoStageInitial,0x080e05dd");
__asm__(".global GetTwoStageActor\n.thumb_set GetTwoStageActor,0x080dd47d");
__asm__(".global ProjectTwoStageActor\n.thumb_set ProjectTwoStageActor,0x080dbdc9");
__asm__(".global CountTwoStageRecordEntries\n.thumb_set CountTwoStageRecordEntries,0x080dd495");
__asm__(".global SetTwoStageActorParameter\n.thumb_set SetTwoStageActorParameter,0x080de10d");
__asm__(".global PositionTwoStageDisplay\n.thumb_set PositionTwoStageDisplay,0x080d49fd");
__asm__(".global CreateTwoStageDisplayEffect\n.thumb_set CreateTwoStageDisplayEffect,0x080d4b65");
__asm__(".global TwoStageDisplayFlagMask\n.thumb_set TwoStageDisplayFlagMask,0x080035a9");
__asm__(".global CreateTwoStageSequence\n.thumb_set CreateTwoStageSequence,0x080d3e9d");
__asm__(".global CreateTwoStageProjected\n.thumb_set CreateTwoStageProjected,0x080d6099");
__asm__(".global CreateTwoStageStage\n.thumb_set CreateTwoStageStage,0x080dfd8d");
__asm__(".global PollTwoStageDisplayEffect\n.thumb_set PollTwoStageDisplayEffect,0x080d4d2d");
__asm__(".global PollTwoStageSequence\n.thumb_set PollTwoStageSequence,0x080d3f09");
__asm__(".global CreateTwoStageActorSequence\n.thumb_set CreateTwoStageActorSequence,0x080ddf69");
__asm__(".global GetTwoStageActorSelector\n.thumb_set GetTwoStageActorSelector,0x080dbc89");
__asm__(".global SetTwoStageProjectedOption\n.thumb_set SetTwoStageProjectedOption,0x080d6195");
__asm__(".global SetTwoStageSequenceOption\n.thumb_set SetTwoStageSequenceOption,0x080d3f85");
__asm__(".global CreateTwoStageTimedSequence\n.thumb_set CreateTwoStageTimedSequence,0x080d4725");
__asm__(".global PollTwoStageProjected\n.thumb_set PollTwoStageProjected,0x080d6135");
__asm__(".global PollTwoStageTimedSequence\n.thumb_set PollTwoStageTimedSequence,0x080d4775");
__asm__(".global IsTwoStageActorFinished\n.thumb_set IsTwoStageActorFinished,0x080de1f1");
__asm__(".global AuthorizeTwoStageTargets\n.thumb_set AuthorizeTwoStageTargets,0x080d8925");
__asm__(".global PollTwoStageChildren\n.thumb_set PollTwoStageChildren,0x080e0571");
__asm__(".global GetTwoStageTarget\n.thumb_set GetTwoStageTarget,0x080dd4a5");
__asm__(".global TwoStageTargetChild\n.thumb_set TwoStageTargetChild,0x080f5f7d");
__asm__(".global CreateTwoStageTask\n.thumb_set CreateTwoStageTask,0x08005b6d");
__asm__(".global CreateTwoStageMotion\n.thumb_set CreateTwoStageMotion,0x080dcfe5");
__asm__(".global PollTwoStageMotion\n.thumb_set PollTwoStageMotion,0x080dba5d");
__asm__(".balign 4,0");
