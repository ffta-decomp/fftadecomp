#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
struct TransitionEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct TransitionWork {
    u16 timer;
    u8 unknown02,variant,ready,unknown05[3];
    TaskNode *followup;
    void *actor;
    TaskNode *initial;
    void *record;
    TaskNode *actor_sequence,*stage;
};
typedef char TransitionEventMustBe28[sizeof(struct TransitionEvent)==28?1:-1];
typedef char TransitionWorkMustBe32[sizeof(struct TransitionWork)==32?1:-1];
extern const u8 TransitionInitialResource[];
extern const u8 TransitionSetupResource[];
extern const u8 TransitionReplacementResource[];
extern const u8 TransitionStageResource[];
extern TaskNode *CreateTransitionInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupTransitionInputs(void);
extern TaskNode *PollTransitionInitial(TaskNode *);
extern u32 CountTransitionTargets(void *,u8);
extern TaskNode *CreateTransitionActorSequence(void *,void **,u16,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void SetTransitionActorOption(void *,u8);
extern void DestroyTransitionActorSequence(TaskNode *);
extern TaskNode *ReplaceTransitionActorSequence(void *,u8,u8 *,const void *,u32,u32,TaskNode *);
extern TaskNode *CreateTransitionStage(const void *,u8,u16,u16,TaskNode *);
extern u32 IsTransitionActorFinished(void *);
extern u32 TransitionDefinitionChild(TaskNode *,struct TransitionEvent *,void *);
extern TaskNode *CreateTransitionTask(u32 (*)(TaskNode *,struct TransitionEvent *,void *),u32,struct TransitionEvent *,TaskNode *);
extern TaskNode *PollTransitionFollowup(TaskNode *);

u32 AdvanceActorSequenceTransitionToFollowUp122(TaskNode *,struct TransitionEvent *,struct TransitionWork *)
    __asm__("OriginalActionCallback_000FA614");
u32 AdvanceActorSequenceTransitionToFollowUp122(TaskNode *task,struct TransitionEvent *event,
                                             struct TransitionWork *work)
{
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=4;
        if(work->variant!=0) count=0;
        work->initial=CreateTransitionInitial(work->record,TransitionInitialResource,count,0,0,task);
        break;
    }
    case 1:
        CleanupTransitionInputs();
        break;
    case 256: {
        TaskNode *initial;
        initial=PollTransitionInitial(work->initial);
        work->initial=initial;
        if(initial!=0) break;
        if((u8)CountTransitionTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        work->actor_sequence=CreateTransitionActorSequence(work->record,&work->actor,144,1,
                             &work->ready,TransitionSetupResource,(u32)initial,(u32)initial,task);
        work->timer=30;
        event->phase++;
        break;
    }
    case 257: {
        u32 raw_timer,remaining;
        raw_timer=(u32)work->timer-1;
        work->timer=raw_timer;
        remaining=(u16)raw_timer;
        if(remaining!=0) break;
        SetTransitionActorOption(work->actor,0);
        DestroyTransitionActorSequence(work->actor_sequence);
        work->actor_sequence=ReplaceTransitionActorSequence(work->actor,1,&work->ready,
                                       TransitionReplacementResource,remaining,remaining,task);
        work->stage=CreateTransitionStage(TransitionStageResource,1,4,0,task);
        event->phase++;
        break;
    }
    case 258: {
        struct TransitionEvent child_event;
        if((u8)IsTransitionActorFinished(work->actor)==0) break;
        DestroyTransitionActorSequence(work->actor_sequence);
        work->actor_sequence=0;
        child_event.definition=122;
        child_event.variant=1;
        child_event.record=work->record;
        work->followup=CreateTransitionTask(TransitionDefinitionChild,28,&child_event,task);
        event->phase++;
        break;
    }
    case 259:
        work->followup=PollTransitionFollowup(work->followup);
        if(work->followup==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateTransitionInitial\n.thumb_set CreateTransitionInitial,0x80e03f9");
__asm__(".global CleanupTransitionInputs\n.thumb_set CleanupTransitionInputs,0x80d38b5");
__asm__(".global PollTransitionInitial\n.thumb_set PollTransitionInitial,0x80e05dd");
__asm__(".global CountTransitionTargets\n.thumb_set CountTransitionTargets,0x80d8859");
__asm__(".global CreateTransitionActorSequence\n.thumb_set CreateTransitionActorSequence,0x80ddf69");
__asm__(".global SetTransitionActorOption\n.thumb_set SetTransitionActorOption,0x80de3bd");
__asm__(".global DestroyTransitionActorSequence\n.thumb_set DestroyTransitionActorSequence,0x80dba51");
__asm__(".global ReplaceTransitionActorSequence\n.thumb_set ReplaceTransitionActorSequence,0x80de4f5");
__asm__(".global CreateTransitionStage\n.thumb_set CreateTransitionStage,0x80dfd8d");
__asm__(".global IsTransitionActorFinished\n.thumb_set IsTransitionActorFinished,0x80de1f1");
__asm__(".global TransitionDefinitionChild\n.thumb_set TransitionDefinitionChild,0x80e6e11");
__asm__(".global CreateTransitionTask\n.thumb_set CreateTransitionTask,0x8005b6d");
__asm__(".global PollTransitionFollowup\n.thumb_set PollTransitionFollowup,0x80e051d");
__asm__(".global TransitionInitialResource\n.set TransitionInitialResource,0x839c82c");
__asm__(".global TransitionSetupResource\n.set TransitionSetupResource,0x839c85c");
__asm__(".global TransitionReplacementResource\n.set TransitionReplacementResource,0x839c860");
__asm__(".global TransitionStageResource\n.set TransitionStageResource,0x839c864");
__asm__(".balign 4,0");
