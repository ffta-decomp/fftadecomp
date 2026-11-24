#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
struct PairedTargetEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct PairedTargetWork {
    u8 count,cursor,spawn_delay,variant,ready,unknown05[3];
    TaskNode *primary,*children[2];
    void *actor;
    TaskNode *initial;
    void *record;
    TaskNode *actor_sequence,*stage;
};
typedef char PairedTargetEventMustBe28[sizeof(struct PairedTargetEvent)==28?1:-1];
typedef char PairedTargetWorkMustBe40[sizeof(struct PairedTargetWork)==40?1:-1];
extern TaskNode *CreatePairedTargetInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupPairedTargetInputs(void);
extern TaskNode *PollPairedTargetInitial(TaskNode *);
extern u32 CountPairedTargetDirect(void *);
extern TaskNode *CreatePairedTargetActorSequence(void *,void **,u16,u8,u8 *,const void *,u8,u8,TaskNode *);
extern void AdvancePairedTargetRecord(void *);
extern u32 IsPairedTargetQueuePending(void);
extern u32 PairedPrimaryChild(TaskNode *,struct PairedTargetEvent *,void *);
extern u32 PairedSecondaryChild(TaskNode *,struct PairedTargetEvent *,void *);
extern TaskNode *CreatePairedTargetTask(u32 (*)(TaskNode *,struct PairedTargetEvent *,void *),u32,struct PairedTargetEvent *,TaskNode *);
extern TaskNode *CreatePairedTargetStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollPairedTargetPrimary(TaskNode *);
extern u32 CountPairedTargetEligible(void *,u8);
extern u32 PollPairedTargetChildren(TaskNode **,u32);
extern void *GetPairedTarget(void *,u8);
extern u32 IsPairedTargetActorFinished(void *);

u32 AdvancePrimaryAndPairedTargetSequence(TaskNode *,struct PairedTargetEvent *,struct PairedTargetWork *)
    __asm__("OriginalActionCallback_000F990C");
u32 AdvancePrimaryAndPairedTargetSequence(TaskNode *task,struct PairedTargetEvent *event,
                                        struct PairedTargetWork *work)
{
    struct PairedTargetEvent primary_event;
    struct PairedTargetEvent target_event;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=4;
        if(work->variant!=0) count=0;
        work->initial=CreatePairedTargetInitial(work->record,(const void *)0x0839C4E8,count,0,0,task);
        break;
    }
    case 1:
        CleanupPairedTargetInputs();
        break;
    case 256: {
        u32 variant;
        work->initial=PollPairedTargetInitial(work->initial);
        if(work->initial!=0) break;
        variant=work->variant;
        if(variant!=0) {
            work->count=CountPairedTargetDirect(work->record);
            work->spawn_delay=1;
            event->phase=260;
            break;
        }
        work->actor_sequence=CreatePairedTargetActorSequence(work->record,&work->actor,32775,2,
                              &work->ready,(const void *)0x0839C544,3,variant,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->ready==0) break;
        AdvancePairedTargetRecord(work->record);
        work->cursor=10;
        event->phase++;
        break;
    case 258: {
        u32 cursor;
        cursor=work->cursor;
        if(cursor!=0) {
            cursor--;
            work->cursor=cursor;
            if((u8)cursor!=0) break;
        }
        if((u8)IsPairedTargetQueuePending()!=0) break;
        primary_event.record=work->record;
        work->primary=CreatePairedTargetTask(PairedPrimaryChild,52,&primary_event,task);
        work->stage=CreatePairedTargetStage((const void *)0x0839C54C,1,4,0,task);
        event->phase++;
        break;
    }
    case 259: {
        u32 raw_count;
        work->primary=PollPairedTargetPrimary(work->primary);
        if(work->primary!=0) break;
        raw_count=CountPairedTargetEligible(work->record,0);
        work->count=raw_count;
        if((u8)raw_count==0) {
            event->phase=261;
            break;
        }
        work->spawn_delay=1;
        event->phase++;
        break;
    }
    case 260: {
        TaskNode **children;
        TaskNode *child;
        u32 raw_delay,first,slot,raw_cursor,next_cursor;
        children=(TaskNode **)(12u+(u32)work);
        PollPairedTargetChildren(children,2);
        raw_delay=(u32)work->spawn_delay-1;
        work->spawn_delay=raw_delay;
        if((u8)raw_delay!=0) break;
        first=(u32)work->children[0];
        slot=((0u-first)|first)>>31;
        target_event.definition=work->cursor;
        target_event.record=GetPairedTarget(work->record,work->cursor);
        child=CreatePairedTargetTask(PairedSecondaryChild,32,&target_event,task);
        children[slot]=child;
        work->spawn_delay=40;
        raw_cursor=(u32)work->cursor+1;
        work->cursor=raw_cursor;
        next_cursor=(u8)raw_cursor;
        if(next_cursor==work->count) event->phase++;
        break;
    }
    case 261:
        if((u8)IsPairedTargetActorFinished(work->actor)==0) break;
        if((u8)PollPairedTargetChildren(&work->children[0],2)!=0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreatePairedTargetInitial\n.thumb_set CreatePairedTargetInitial,0x80e03f9");
__asm__(".global CleanupPairedTargetInputs\n.thumb_set CleanupPairedTargetInputs,0x80d38b5");
__asm__(".global PollPairedTargetInitial\n.thumb_set PollPairedTargetInitial,0x80e05dd");
__asm__(".global CountPairedTargetDirect\n.thumb_set CountPairedTargetDirect,0x80dd495");
__asm__(".global CreatePairedTargetActorSequence\n.thumb_set CreatePairedTargetActorSequence,0x80ddf69");
__asm__(".global AdvancePairedTargetRecord\n.thumb_set AdvancePairedTargetRecord,0x80d8cd5");
__asm__(".global IsPairedTargetQueuePending\n.thumb_set IsPairedTargetQueuePending,0x80d8b4d");
__asm__(".global PairedPrimaryChild\n.thumb_set PairedPrimaryChild,0x80f9525");
__asm__(".global PairedSecondaryChild\n.thumb_set PairedSecondaryChild,0x80f9839");
__asm__(".global CreatePairedTargetTask\n.thumb_set CreatePairedTargetTask,0x8005b6d");
__asm__(".global CreatePairedTargetStage\n.thumb_set CreatePairedTargetStage,0x80dfd8d");
__asm__(".global PollPairedTargetPrimary\n.thumb_set PollPairedTargetPrimary,0x80e051d");
__asm__(".global CountPairedTargetEligible\n.thumb_set CountPairedTargetEligible,0x80d8859");
__asm__(".global PollPairedTargetChildren\n.thumb_set PollPairedTargetChildren,0x80e0571");
__asm__(".global GetPairedTarget\n.thumb_set GetPairedTarget,0x80dd4a5");
__asm__(".global IsPairedTargetActorFinished\n.thumb_set IsPairedTargetActorFinished,0x80de1f1");
