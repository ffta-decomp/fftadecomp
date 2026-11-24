#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct OpeningActionEvent {
    u16 phase;
    u8 unknown02[2];
    void *argument;
    u8 unknown08[12];
    u16 parameter, variant;
    u8 unknown18[4];
};
struct OpeningActionWork {
    u8 variant, target_count;
    s16 x, y;
    u8 ordinal, delay, complete;
    u8 unknown09[3];
    void *actor;
    TaskNode *targets[2];
    TaskNode *opening[3];
    void *resources[2];
    TaskNode *projected, *sequence, *initial;
    void *record;
    TaskNode *actor_sequence, *stage;
};
typedef char OpeningEventMustBe28[sizeof(struct OpeningActionEvent)==28?1:-1];
typedef char OpeningWorkMustBe68[sizeof(struct OpeningActionWork)==68?1:-1];
extern TaskNode *CreateOpeningInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupOpeningInputs(void);
extern TaskNode *PollOpeningInitial(TaskNode *);
extern u32 CountOpeningTargets(void *,u8);
extern TaskNode *CreateOpeningActorSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern void *CopyOpeningParameters(void *,const void *,u32);
extern void ProjectOpeningActor(void *,s16 *,s16 *);
extern TaskNode *CreateOpeningProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern u32 OpeningPositionChild(TaskNode *,struct OpeningActionEvent *,void *);
extern u32 OpeningTargetChild(TaskNode *,struct OpeningActionEvent *,void *);
extern TaskNode *CreateOpeningTask(u32 (*)(TaskNode *,struct OpeningActionEvent *,void *),u32,struct OpeningActionEvent *,TaskNode *);
extern TaskNode *CreateOpeningSequence(const void *,TaskNode *,u16);
extern TaskNode *CreateOpeningStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollOpeningSequence(TaskNode *);
extern TaskNode *PollOpeningProjected(TaskNode *);
extern u32 PollOpeningChildren(TaskNode **,u8);
extern void *GetOpeningTarget(void *,u8);
extern u32 IsOpeningActorFinished(void *);

u32 AdvanceOpeningTrioAndTargetChildren(TaskNode *,struct OpeningActionEvent *,struct OpeningActionWork *)
    __asm__("OriginalActionCallback_000F41C8");
u32 AdvanceOpeningTrioAndTargetChildren(TaskNode *task,struct OpeningActionEvent *event,
                                      struct OpeningActionWork *work)
{
    struct OpeningActionEvent opening_event;
    u8 opening_parameters[3];
    struct OpeningActionEvent target_event;
    u32 position;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->argument;
        count=4;
        if(work->variant!=0) count=0;
        work->initial=CreateOpeningInitial(work->record,(const void *)0x0839AF60,count,0,0,task);
        break;
    }
    case 1:
        CleanupOpeningInputs();
        break;
    case 256: {
        u8 variant;
        work->initial=PollOpeningInitial(work->initial);
        if(work->initial!=0) break;
        variant=work->variant;
        if(variant!=0) {
            work->delay=1;
            work->target_count=CountOpeningTargets(work->record,0);
            if(work->target_count==0) event->phase=260;
            else event->phase=259;
            break;
        }
        work->actor_sequence=CreateOpeningActorSequence(work->record,&work->actor,60,2,
                                                        &work->complete,(const void *)0x0839B01C,
                                                        variant,variant,task);
        event->phase++;
        break;
    }
    case 257: {
        register u32 index __asm__("r5");
        u8 complete;
        u8 *copy_destination;
        u8 *parameters;
        copy_destination=opening_parameters;
        CopyOpeningParameters(copy_destination,(const void *)0x08149D10,3);
        complete=work->complete;
        parameters=copy_destination;
        /* The copied buffer gets its distinct post-call reading lifetime. */
        __asm__("" : "+r"(parameters) : "r"(copy_destination));
        if(complete==0) break;
        ProjectOpeningActor(work->actor,&work->x,&work->y);
        work->projected=CreateOpeningProjected(work->x,(s16)((u16)work->y+28),0,1,2,
                                               work->resources,(const void *)0x0839AF90,task);
        {
            u32 high_y;
            register u32 low_x __asm__("r0");
            high_y=(u32)(u16)work->y<<16;
            low_x=(u16)work->x;
            low_x|=high_y;
            /* The original complete packed word, not just its X input,
             * reaches the physical SP80 store through R0. */
            __asm__("" : "+r"(low_x));
            position=low_x;
        }
        opening_event.argument=&position;
        index=0;
        do {
            register u32 next_index __asm__("r0");
            /* The native carrier is a complete word, narrowed at its update. */
            __asm__("" : "+r"(index));
            opening_event.parameter=parameters[index];
            opening_event.variant=index;
            work->opening[index]=CreateOpeningTask(OpeningPositionChild,28,&opening_event,task);
            next_index=index+1;
            /* Raw ADD result is consumed before publishing the LOW8 index. */
            __asm__("" : "+r"(next_index));
            index=(u8)next_index;
        } while(index<=2);
        work->sequence=CreateOpeningSequence((const void *)0x08949F18,task,16);
        work->stage=CreateOpeningStage((const void *)0x0839B024,1,4,0,task);
        event->phase++;
        break;
    }
    case 258:
        work->sequence=PollOpeningSequence(work->sequence);
        if(work->sequence!=0) break;
        work->projected=PollOpeningProjected(work->projected);
        if(work->projected!=0) break;
        if((u8)PollOpeningChildren(work->opening,3)==0) break;
        work->delay=1;
        work->target_count=CountOpeningTargets(work->record,0);
        if(work->target_count==0) event->phase=260;
        else event->phase++;
        break;
    case 259: {
        TaskNode **targets;
        u32 bits, slot;
        targets=work->targets;
        PollOpeningChildren(targets,2);
        work->delay--;
        if(work->delay!=0) break;
        bits=(u32)targets[0];
        slot=((0U-bits)|bits)>>31;
        target_event.parameter=work->ordinal;
        target_event.argument=GetOpeningTarget(work->record,work->ordinal);
        targets[slot]=CreateOpeningTask(OpeningTargetChild,40,&target_event,task);
        work->delay=50;
        work->ordinal++;
        if(work->ordinal==work->target_count) event->phase++;
        break;
    }
    case 260:
        if((u8)IsOpeningActorFinished(work->actor)==0) break;
        if((u8)PollOpeningChildren(work->targets,2)!=0) event->phase=2;
        break;
    }
    return 0;
}

__asm__(".global CreateOpeningInitial\n.thumb_set CreateOpeningInitial,0x080e03f9");
__asm__(".global CleanupOpeningInputs\n.thumb_set CleanupOpeningInputs,0x080d38b5");
__asm__(".global PollOpeningInitial\n.thumb_set PollOpeningInitial,0x080e05dd");
__asm__(".global CountOpeningTargets\n.thumb_set CountOpeningTargets,0x080d8859");
__asm__(".global CreateOpeningActorSequence\n.thumb_set CreateOpeningActorSequence,0x080ddf69");
__asm__(".global CopyOpeningParameters\n.thumb_set CopyOpeningParameters,0x081443fd");
__asm__(".global ProjectOpeningActor\n.thumb_set ProjectOpeningActor,0x080dbdc9");
__asm__(".global CreateOpeningProjected\n.thumb_set CreateOpeningProjected,0x080d6099");
__asm__(".global OpeningPositionChild\n.thumb_set OpeningPositionChild,0x080f3f7d");
__asm__(".global OpeningTargetChild\n.thumb_set OpeningTargetChild,0x080f40dd");
__asm__(".global CreateOpeningTask\n.thumb_set CreateOpeningTask,0x08005b6d");
__asm__(".global CreateOpeningSequence\n.thumb_set CreateOpeningSequence,0x080d4725");
__asm__(".global CreateOpeningStage\n.thumb_set CreateOpeningStage,0x080dfd8d");
__asm__(".global PollOpeningSequence\n.thumb_set PollOpeningSequence,0x080d4775");
__asm__(".global PollOpeningProjected\n.thumb_set PollOpeningProjected,0x080d6135");
__asm__(".global PollOpeningChildren\n.thumb_set PollOpeningChildren,0x080e0571");
__asm__(".global GetOpeningTarget\n.thumb_set GetOpeningTarget,0x080dd4a5");
__asm__(".global IsOpeningActorFinished\n.thumb_set IsOpeningActorFinished,0x080de1f1");
__asm__(".balign 4,0");
