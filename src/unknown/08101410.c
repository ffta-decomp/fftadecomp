#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
struct RequestEvent {
    u16 phase,unknown02;
    void *record,*shared;
    u32 word12,word16;
    u16 definition,variant;
    u32 word24;
};
struct RequestTarget {u8 unknown00[14];u16 field14;};
struct RequestWork {
    s16 x,y;
    u16 timer;
    u8 variant,ready,special,unknown09[3];
    TaskNode *child;
    void *actor,*projected,*record;
    TaskNode *initial;
    u8 positioned_output[8];
    TaskNode *positioned,*secondary,*stage;
};
typedef char RequestEventSize[sizeof(struct RequestEvent)==28?1:-1];
typedef char RequestWorkSize[sizeof(struct RequestWork)==52?1:-1];
extern const u8 RequestInitialResource[],RequestPositionedResource[],RequestSecondaryResource[],RequestStageResource[];
extern TaskNode *CreateRequestInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupRequestInputs(void);
extern TaskNode *PollRequestInitial(TaskNode *);
extern u32 ShouldSkipRequestSequence(void *);
extern struct RequestTarget *GetRequestTarget(void *,u8);
extern u32 RequestMotionChild(TaskNode *,struct RequestEvent *,void *);
extern TaskNode *CreateRequestChild(u32 (*)(TaskNode *,struct RequestEvent *,void *),u32,struct RequestEvent *,TaskNode *);
extern void *GetRequestActor(void *);
extern void SetRequestActorMode(void *,u32);
extern void RestoreRequestActorMotion(void *);
extern u32 CountRequestTargets(void *,u8);
extern void ReadRequestActorCoordinates(void *,s16 *,s16 *,s16 *);
extern TaskNode *CreateRequestSpecial(struct RequestTarget *,u16,u8,u8,u8,u32,TaskNode *);
extern void *ProjectRequestTarget(struct RequestTarget *,s16 *,s16 *,u8);
extern TaskNode *CreateRequestPositioned(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateRequestSecondary(struct RequestTarget *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *CreateRequestStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollRequestChild(TaskNode *);
extern TaskNode *PollRequestPositioned(TaskNode *);
extern TaskNode *PollRequestSecondary(TaskNode *);

u32 AdvanceCoordinatedActorRequestSequence(TaskNode *,struct RequestEvent *,struct RequestWork *)
    __asm__("OriginalActionCallback_00101410");
u32 AdvanceCoordinatedActorRequestSequence(TaskNode *task,struct RequestEvent *event,struct RequestWork *work)
{
    u16 entry_phase=event->phase;
    switch(entry_phase) {
    case 0: {
        u16 variant;
        void *record;
        u8 count;
        variant=event->variant;
        work->variant=variant;
        record=event->record;
        work->record=record;
        count=4;
        if((u8)variant!=0) count=0;
        work->initial=CreateRequestInitial(record,RequestInitialResource,count,0,(const s16 *)(u32)entry_phase,task);
        break;
    }
    case 1:
        CleanupRequestInputs();
        break;
    case 256: {
        struct RequestEvent child_event;
        work->initial=PollRequestInitial(work->initial);
        if(work->initial!=0) break;
        if((u8)ShouldSkipRequestSequence(work->record)!=0) {
            event->phase=2;
            break;
        }
        if(GetRequestTarget(work->record,0)->field14==6) work->special=1;
        child_event.definition=work->special;
        child_event.record=work->record;
        child_event.shared=&work->ready;
        work->child=CreateRequestChild(RequestMotionChild,144,&child_event,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->ready!=1) break;
        work->actor=GetRequestActor(work->record);
        SetRequestActorMode(work->actor,140);
        work->timer=16;
        event->phase++;
        break;
    case 258:
        work->timer--;
        if(work->timer!=0) break;
        work->ready=2;
        event->phase++;
        break;
    case 259:
        if(work->ready!=3) break;
        RestoreRequestActorMotion(work->actor);
        event->phase++;
        break;
    case 260: {
        u32 ready_state;
        struct RequestTarget *target;
        ready_state=work->ready;
        if(ready_state!=4) break;
        if((u8)CountRequestTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        target=GetRequestTarget(work->record,0);
        if(work->special!=0) {
            s16 x,y,z;
            ReadRequestActorCoordinates(work->actor,&x,&y,&z);
            work->secondary=CreateRequestSpecial(target,977,6,(u8)x,(u8)z,0,task);
        } else {
            work->projected=ProjectRequestTarget(target,&work->x,&work->y,0);
            work->positioned=CreateRequestPositioned(work->x,work->y,0,1,2,work->positioned_output,
                                                   RequestPositionedResource,task);
            work->secondary=CreateRequestSecondary(target,RequestSecondaryResource,12,20,ready_state,task,20);
            work->stage=CreateRequestStage(RequestStageResource,1,4,0,task);
        }
        event->phase++;
        break;
    }
    case 261:
        work->child=PollRequestChild(work->child);
        if(work->child!=0) break;
        work->positioned=PollRequestPositioned(work->positioned);
        if(work->positioned!=0) break;
        work->secondary=PollRequestSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateRequestInitial\n.thumb_set CreateRequestInitial,0x80e03f9");
__asm__(".global CleanupRequestInputs\n.thumb_set CleanupRequestInputs,0x80d38b5");
__asm__(".global PollRequestInitial\n.thumb_set PollRequestInitial,0x80e05dd");
__asm__(".global ShouldSkipRequestSequence\n.thumb_set ShouldSkipRequestSequence,0x80d3b55");
__asm__(".global GetRequestTarget\n.thumb_set GetRequestTarget,0x80dd4a5");
__asm__(".global RequestMotionChild\n.thumb_set RequestMotionChild,0x8100ef1");
__asm__(".global CreateRequestChild\n.thumb_set CreateRequestChild,0x8005b6d");
__asm__(".global GetRequestActor\n.thumb_set GetRequestActor,0x80dd47d");
__asm__(".global SetRequestActorMode\n.thumb_set SetRequestActorMode,0x80de10d");
__asm__(".global RestoreRequestActorMotion\n.thumb_set RestoreRequestActorMotion,0x80de391");
__asm__(".global CountRequestTargets\n.thumb_set CountRequestTargets,0x80d8859");
__asm__(".global ReadRequestActorCoordinates\n.thumb_set ReadRequestActorCoordinates,0x80dbd79");
__asm__(".global CreateRequestSpecial\n.thumb_set CreateRequestSpecial,0x80dfa31");
__asm__(".global ProjectRequestTarget\n.thumb_set ProjectRequestTarget,0x80dd749");
__asm__(".global CreateRequestPositioned\n.thumb_set CreateRequestPositioned,0x80d6099");
__asm__(".global CreateRequestSecondary\n.thumb_set CreateRequestSecondary,0x80dcfe5");
__asm__(".global CreateRequestStage\n.thumb_set CreateRequestStage,0x80dfd8d");
__asm__(".global PollRequestChild\n.thumb_set PollRequestChild,0x80e051d");
__asm__(".global PollRequestPositioned\n.thumb_set PollRequestPositioned,0x80d6135");
__asm__(".global PollRequestSecondary\n.thumb_set PollRequestSecondary,0x80dba5d");
__asm__(".global RequestInitialResource\n.set RequestInitialResource,0x839ead4");
__asm__(".global RequestPositionedResource\n.set RequestPositionedResource,0x839eb04");
__asm__(".global RequestSecondaryResource\n.set RequestSecondaryResource,0x839eb34");
__asm__(".global RequestStageResource\n.set RequestStageResource,0x839eb50");
