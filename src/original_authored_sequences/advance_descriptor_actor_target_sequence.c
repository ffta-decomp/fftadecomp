typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct DescriptorActionEvent {
    u16 phase;
    u8 unknown02[2];
    void *record;
    u8 unknown08[4];
    u32 flags;
    u8 unknown10[4];
    s16 descriptor;
    u16 variant;
    u8 unknown18[4];
};
/* The same aligned halfword has two independently written byte views. */
union DescriptorActionMode {
    u16 word;
    u8 bytes[2];
} __attribute__((packed, aligned(2)));
struct DescriptorActionWork {
    s16 x, y;
    union DescriptorActionMode mode;
    u8 variant;
    s8 last_target;
    u8 delay, unknown09;
    u16 timer_ordinal;
    u8 complete, unknown0D[3];
    void *resource0;
    TaskNode *projected0;
    void *resources1[3];
    TaskNode *projected1, *display_effect, *sequence, *children[4];
    void *actor;
    TaskNode *sequences[2], *motion;
    void *record;
    TaskNode *initial, *actor_sequence, *stage;
};
typedef char DescriptorEventMustBe28[sizeof(struct DescriptorActionEvent)==28?1:-1];
typedef char DescriptorWorkMustBe96[sizeof(struct DescriptorActionWork)==96?1:-1];
typedef char DescriptorModeMustBe2[sizeof(union DescriptorActionMode)==2?1:-1];
extern u16 DescriptorDisplayFlags;
extern TaskNode *CreateDescriptorInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDescriptorInputs(void);
extern TaskNode *PollDescriptorInitial(TaskNode *);
extern void *GetDescriptorActor(void *);
extern void SetDescriptorActorParameter(void *,u8);
extern TaskNode *CreateDescriptorActorSequence(void *,void *,u8,u8,u32,u32,u32,TaskNode *);
extern TaskNode *CreateDescriptorStage(const void *,u8,u16,u16,TaskNode *);
extern void ProjectDescriptorActor(void *,s16 *,s16 *);
extern u32 CountDescriptorRecordEntries(void *);
extern TaskNode *CreateDescriptorCue(const void *,u32,u32,s32,s32,u32);
extern TaskNode *CreateDescriptorSequence(const void *,TaskNode *);
extern TaskNode *CreateDescriptorTimedSequence(const void *,TaskNode *,u16);
extern TaskNode *CreateDescriptorControlSequence(const void *,TaskNode *);
extern u32 PollDescriptorSequenceArray(TaskNode **,u8);
extern u32 DescriptorDisplayFlagMask(u8);
extern void PositionDescriptorDisplay(u8,u8,u8,s32,s32);
extern TaskNode *CreateDescriptorDisplayEffect(u8,const void *,u16,u8);
extern TaskNode *CreateDescriptorProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern void SetDescriptorActorPhase(void *,u8);
extern TaskNode *PollDescriptorDisplayEffect(TaskNode *,u8);
extern TaskNode *PollDescriptorControlSequence(TaskNode *);
extern TaskNode *CreateDescriptorActorMotion(void *,u8,u16,TaskNode *);
extern TaskNode *PollDescriptorProjected(TaskNode *);
extern u32 AuthorizeDescriptorTargets(void *,u8,u16,TaskNode *);
extern u32 PollDescriptorChildren(TaskNode **,u8);
extern void *GetDescriptorTarget(void *,u8);
extern u32 DescriptorTargetChild(TaskNode *,struct DescriptorActionEvent *,void *);
extern TaskNode *CreateDescriptorTask(u32 (*)(TaskNode *,struct DescriptorActionEvent *,void *),u32,struct DescriptorActionEvent *,TaskNode *);
extern TaskNode *PollDescriptorMotion(TaskNode *);
extern void FinishDescriptorActor(void *,u8);

u32 AdvanceDescriptorActorTargetSequence(TaskNode *,struct DescriptorActionEvent *,struct DescriptorActionWork *)
    __asm__("OriginalActionCallback_000F6520");
u32 AdvanceDescriptorActorTargetSequence(TaskNode *task,struct DescriptorActionEvent *event,
                                       struct DescriptorActionWork *work)
{
    struct DescriptorActionEvent child_event;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        work->mode.bytes[0]=0;
        work->mode.bytes[1]=0;
        if(event->descriptor==266) {
            work->mode.bytes[0]=1;
            if((event->flags&2)!=0) work->mode.bytes[1]=1;
        }
        count=6;
        if(work->variant!=0) count=0;
        work->initial=CreateDescriptorInitial(work->record,(const void *)0x0839B800,count,0,0,task);
        break;
    }
    case 1:
        CleanupDescriptorInputs();
        break;
    case 256: {
        void *actor;
        u8 flag;
        work->initial=PollDescriptorInitial(work->initial);
        if(work->initial!=0) break;
        actor=GetDescriptorActor(work->record);
        work->actor=actor;
        if(work->mode.bytes[0]==0) {
            SetDescriptorActorParameter(actor,36);
            event->phase=258;
            break;
        }
        flag=work->mode.bytes[1];
        if(flag!=0) {
            SetDescriptorActorParameter(actor,36);
            work->timer_ordinal=60;
        } else {
            SetDescriptorActorParameter(actor,84);
            work->actor_sequence=CreateDescriptorActorSequence(work->actor,&work->complete,2,2,
                                                                 flag,flag,flag,task);
        }
        work->stage=CreateDescriptorStage((const void *)0x0839B8BC,1,4,0,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->timer_ordinal!=0) {
            work->timer_ordinal--;
            if(work->timer_ordinal!=0) break;
        }
        if(work->actor_sequence!=0 && work->complete==0) break;
        event->phase++;
        break;
    case 258: {
        u8 variant;
        ProjectDescriptorActor(work->actor,&work->x,&work->y);
        variant=work->variant;
        if(variant!=0) {
            work->last_target=CountDescriptorRecordEntries(work->record)-1;
            work->delay=1;
            event->phase=262;
            break;
        }
        CreateDescriptorCue((const void *)0x088F58EC,0,2,work->x,work->y,variant);
        work->sequences[0]=CreateDescriptorSequence((const void *)0x0894A07C,task);
        work->sequences[1]=CreateDescriptorSequence((const void *)0x0894A0B0,task);
        work->sequence=CreateDescriptorControlSequence((const void *)0x0894D69C,task);
        work->stage=CreateDescriptorStage((const void *)0x0839B8C4,1,4,0,task);
        event->phase++;
        break;
    }
    case 259:
        if((u8)PollDescriptorSequenceArray(work->sequences,2)==0) break;
        {
            u32 mask;
            mask=DescriptorDisplayFlagMask(2);
            DescriptorDisplayFlags&=~mask;
        }
        PositionDescriptorDisplay(0,2,0,work->x,work->y);
        work->display_effect=CreateDescriptorDisplayEffect(0,(const void *)0x088EF6CC,684,7);
        {
            u32 mask;
            register u32 control __asm__("r1");
            mask=DescriptorDisplayFlagMask(2);
            control=DescriptorDisplayFlags;
            /* Original OR consumes the fresh halfword as its working value. */
            __asm__("" : "+r"(control));
            control|=mask;
            DescriptorDisplayFlags=control;
        }
        work->sequences[0]=CreateDescriptorSequence((const void *)0x0894A0E8,task);
        work->sequences[1]=CreateDescriptorTimedSequence((const void *)0x0894AAB0,task,26);
        work->projected0=CreateDescriptorProjected(work->x,work->y,0,1,1,
                                      &work->resource0,(const void *)0x0839B848,task);
        work->stage=CreateDescriptorStage((const void *)0x0839B8CC,1,4,0,task);
        if(work->mode.word==1) work->timer_ordinal=16;
        event->phase++;
        break;
    case 260:
        if(work->timer_ordinal!=0) {
            u32 raw_timer;
            u16 timer;
            raw_timer=(u32)work->timer_ordinal-1;
            work->timer_ordinal=raw_timer;
            timer=(u16)raw_timer;
            if(timer==0) {
                SetDescriptorActorPhase(work->actor,0);
                work->actor_sequence=CreateDescriptorActorSequence(work->actor,&work->complete,2,3,
                                                                    timer,timer,timer,task);
            }
        }
        work->display_effect=PollDescriptorDisplayEffect(work->display_effect,0);
        if(work->display_effect!=0) break;
        {
            u32 mask;
            mask=DescriptorDisplayFlagMask(2);
            DescriptorDisplayFlags&=~mask;
        }
        work->sequence=PollDescriptorControlSequence(work->sequence);
        if(work->sequence!=0) break;
        if((u8)PollDescriptorSequenceArray(work->sequences,2)==0) break;
        work->projected1=CreateDescriptorProjected(work->x,work->y,0,1,3,
                                      work->resources1,(const void *)0x0839B860,task);
        work->stage=CreateDescriptorStage((const void *)0x0839B8D4,1,4,0,task);
        work->motion=CreateDescriptorActorMotion(work->actor,1,30,task);
        event->phase++;
        break;
    case 261:
        work->projected0=PollDescriptorProjected(work->projected0);
        if(work->projected0!=0) break;
        work->projected1=PollDescriptorProjected(work->projected1);
        if(work->projected1!=0) break;
        work->last_target=AuthorizeDescriptorTargets(work->record,0,56,task)-1;
        if(work->last_target<=0) {
            event->phase=263;
            break;
        }
        work->delay=1;
        event->phase++;
        break;
    case 262: {
        TaskNode **children;
        TaskNode *child;
        TaskNode **destination;
        u32 byte_offset;
        children=work->children;
        PollDescriptorChildren(children,4);
        work->delay--;
        if(work->delay!=0) break;
        child_event.descriptor=work->timer_ordinal;
        child_event.record=GetDescriptorTarget(work->record,(u8)work->timer_ordinal);
        child=CreateDescriptorTask(DescriptorTargetChild,20,&child_event,task);
        byte_offset=(u32)work->timer_ordinal<<2;
        destination=(TaskNode **)((u8 *)children+byte_offset);
        *destination=child;
        work->delay=30;
        work->timer_ordinal++;
        if(work->timer_ordinal==work->last_target) event->phase++;
        break;
    }
    case 263:
        work->motion=PollDescriptorMotion(work->motion);
        if(work->motion!=0) break;
        if((u8)PollDescriptorChildren(work->children,4)==0) break;
        FinishDescriptorActor(work->actor,16);
        event->phase=2;
        break;
    }
    return 0;
}

__asm__(".global DescriptorDisplayFlags\n.set DescriptorDisplayFlags,0x03000940");
__asm__(".global CreateDescriptorInitial\n.thumb_set CreateDescriptorInitial,0x080e03f9");
__asm__(".global CleanupDescriptorInputs\n.thumb_set CleanupDescriptorInputs,0x080d38b5");
__asm__(".global PollDescriptorInitial\n.thumb_set PollDescriptorInitial,0x080e05dd");
__asm__(".global GetDescriptorActor\n.thumb_set GetDescriptorActor,0x080dd47d");
__asm__(".global SetDescriptorActorParameter\n.thumb_set SetDescriptorActorParameter,0x080de10d");
__asm__(".global CreateDescriptorActorSequence\n.thumb_set CreateDescriptorActorSequence,0x080de4b1");
__asm__(".global CreateDescriptorStage\n.thumb_set CreateDescriptorStage,0x080dfd8d");
__asm__(".global ProjectDescriptorActor\n.thumb_set ProjectDescriptorActor,0x080dbdc9");
__asm__(".global CountDescriptorRecordEntries\n.thumb_set CountDescriptorRecordEntries,0x080dd495");
__asm__(".global CreateDescriptorCue\n.thumb_set CreateDescriptorCue,0x080d7221");
__asm__(".global CreateDescriptorSequence\n.thumb_set CreateDescriptorSequence,0x080d4705");
__asm__(".global CreateDescriptorTimedSequence\n.thumb_set CreateDescriptorTimedSequence,0x080d4725");
__asm__(".global CreateDescriptorControlSequence\n.thumb_set CreateDescriptorControlSequence,0x080d3e9d");
__asm__(".global PollDescriptorSequenceArray\n.thumb_set PollDescriptorSequenceArray,0x080d48dd");
__asm__(".global DescriptorDisplayFlagMask\n.thumb_set DescriptorDisplayFlagMask,0x080035a9");
__asm__(".global PositionDescriptorDisplay\n.thumb_set PositionDescriptorDisplay,0x080d49fd");
__asm__(".global CreateDescriptorDisplayEffect\n.thumb_set CreateDescriptorDisplayEffect,0x080d4b65");
__asm__(".global CreateDescriptorProjected\n.thumb_set CreateDescriptorProjected,0x080d6099");
__asm__(".global SetDescriptorActorPhase\n.thumb_set SetDescriptorActorPhase,0x080de3bd");
__asm__(".global PollDescriptorDisplayEffect\n.thumb_set PollDescriptorDisplayEffect,0x080d4d2d");
__asm__(".global PollDescriptorControlSequence\n.thumb_set PollDescriptorControlSequence,0x080d3f09");
__asm__(".global CreateDescriptorActorMotion\n.thumb_set CreateDescriptorActorMotion,0x080df8e9");
__asm__(".global PollDescriptorProjected\n.thumb_set PollDescriptorProjected,0x080d6135");
__asm__(".global AuthorizeDescriptorTargets\n.thumb_set AuthorizeDescriptorTargets,0x080d8925");
__asm__(".global PollDescriptorChildren\n.thumb_set PollDescriptorChildren,0x080e0571");
__asm__(".global GetDescriptorTarget\n.thumb_set GetDescriptorTarget,0x080dd4a5");
__asm__(".global DescriptorTargetChild\n.thumb_set DescriptorTargetChild,0x080f6491");
__asm__(".global CreateDescriptorTask\n.thumb_set CreateDescriptorTask,0x08005b6d");
__asm__(".global PollDescriptorMotion\n.thumb_set PollDescriptorMotion,0x080dba5d");
__asm__(".global FinishDescriptorActor\n.thumb_set FinishDescriptorActor,0x080dd721");
__asm__(".balign 4,0");
