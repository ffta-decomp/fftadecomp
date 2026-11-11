#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct FirstTargetEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition,variant;
    u8 unknown18[4];
};
struct FirstTargetWork {
    u8 variant,unknown01[3];
    void *actor,*record;
    TaskNode *initial;
    u8 resource[4];
    void *projected;
    TaskNode *secondary,*stage;
};
typedef char FirstTargetWorkMustBe32[sizeof(struct FirstTargetWork)==32?1:-1];
extern TaskNode *CreateFirstTargetInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupFirstTargetInputs(void);
extern TaskNode *PollFirstTargetInitial(TaskNode *);
extern u32 ShouldSkipFirstTargetSequence(void *);
extern void *GetFirstTargetActor(void *);
extern void SetFirstTargetActorMotion(void *,u16);
extern void SetFirstTargetActorOption(void *,u8);
extern void ProjectFirstTargetActor(void *,s16 *,s16 *);
extern void *CreateFirstTargetProjected(s32,s32,u32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateFirstTargetStage(const void *,u8,u16,u16,TaskNode *);
extern u32 CountFirstTargetEligible(void *,u8);
extern void *PollFirstTargetProjected(void *);
extern void *GetFirstTarget(void *,u8);
extern TaskNode *CreateFirstTargetSecondary(void *,const void *,u8,u16,u32,TaskNode *,u32);
extern TaskNode *PollFirstTargetSecondary(TaskNode *);

u32 AdvanceFirstTargetProjectedSequence(TaskNode *,struct FirstTargetEvent *,struct FirstTargetWork *)
    __asm__("OriginalActionCallback_000F93E0");
u32 AdvanceFirstTargetProjectedSequence(TaskNode *task,struct FirstTargetEvent *event,
                                      struct FirstTargetWork *work)
{
    s16 x,y;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=2;
        if(work->variant!=0) count=0;
        work->initial=CreateFirstTargetInitial(work->record,(const void *)0x0839C464,count,0,0,task);
        break;
    }
    case 1:
        CleanupFirstTargetInputs();
        break;
    case 256:
        work->initial=PollFirstTargetInitial(work->initial);
        if(work->initial!=0) break;
        if((u8)ShouldSkipFirstTargetSequence(work->record)!=0) {
            event->phase=2;
            break;
        }
        work->actor=GetFirstTargetActor(work->record);
        SetFirstTargetActorMotion(work->actor,36);
        SetFirstTargetActorOption(work->actor,1);
        ProjectFirstTargetActor(work->actor,&x,&y);
        work->projected=CreateFirstTargetProjected(x,y,0,1,1,&work->resource[0],
                                                    (const void *)0x0839C47C,task);
        work->stage=CreateFirstTargetStage((const void *)0x0839C4A8,2,4,0,task);
        event->phase++;
        break;
    case 257: {
        void *projected,*target;
        if((u8)CountFirstTargetEligible(work->record,0)==0) {
            event->phase=2;
            break;
        }
        projected=PollFirstTargetProjected(work->projected);
        work->projected=projected;
        if(projected!=0) break;
        target=GetFirstTarget(work->record,0);
        work->secondary=CreateFirstTargetSecondary(target,(const void *)0x0839C494,12,0,
                                                    4,task,(u32)projected);
        event->phase++;
        break;
    }
    case 258:
        work->secondary=PollFirstTargetSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateFirstTargetInitial\n.thumb_set CreateFirstTargetInitial,0x80e03f9");
__asm__(".global CleanupFirstTargetInputs\n.thumb_set CleanupFirstTargetInputs,0x80d38b5");
__asm__(".global PollFirstTargetInitial\n.thumb_set PollFirstTargetInitial,0x80e05dd");
__asm__(".global ShouldSkipFirstTargetSequence\n.thumb_set ShouldSkipFirstTargetSequence,0x80d3b55");
__asm__(".global GetFirstTargetActor\n.thumb_set GetFirstTargetActor,0x80dd47d");
__asm__(".global SetFirstTargetActorMotion\n.thumb_set SetFirstTargetActorMotion,0x80de10d");
__asm__(".global SetFirstTargetActorOption\n.thumb_set SetFirstTargetActorOption,0x80de3bd");
__asm__(".global ProjectFirstTargetActor\n.thumb_set ProjectFirstTargetActor,0x80dbdc9");
__asm__(".global CreateFirstTargetProjected\n.thumb_set CreateFirstTargetProjected,0x80d6099");
__asm__(".global CreateFirstTargetStage\n.thumb_set CreateFirstTargetStage,0x80dfd8d");
__asm__(".global CountFirstTargetEligible\n.thumb_set CountFirstTargetEligible,0x80d8859");
__asm__(".global PollFirstTargetProjected\n.thumb_set PollFirstTargetProjected,0x80d6135");
__asm__(".global GetFirstTarget\n.thumb_set GetFirstTarget,0x80dd4a5");
__asm__(".global CreateFirstTargetSecondary\n.thumb_set CreateFirstTargetSecondary,0x80dcfe5");
__asm__(".global PollFirstTargetSecondary\n.thumb_set PollFirstTargetSecondary,0x80dba5d");
__asm__(".balign 4,0");
