#include "ffta/types.h"
typedef struct TaskNode TaskNode;
struct ThreeStageEvent {
    u16 phase, unknown02;
    void *record;
    u8 unknown08[12];
    u16 definition, variant;
    u8 unknown18[4];
};
struct ThreeStageWork {
    u8 unknown00, variant, actor_ready, unknown03, count, delay;
    u16 ordinal;
    void *resources[3];
    TaskNode *projected, *children[4];
    void *actor;
    TaskNode *stages[3];
    void *record;
    TaskNode *initial, *actor_sequence, *stage;
};
typedef char ThreeStageEventMustBe28[sizeof(struct ThreeStageEvent)==28?1:-1];
typedef char ThreeStageWorkMustBe72[sizeof(struct ThreeStageWork)==72?1:-1];
extern TaskNode *CreateThreeStageInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupThreeStageInputs(void);
extern TaskNode *PollThreeStageInitial(TaskNode *);
extern u32 CountThreeStageDirectTargets(void *);
extern TaskNode *CreateThreeStageActorSequence(void *,void **,u16,u8,u8 *,const void *,u8,u8,TaskNode *);
extern void ProjectThreeStageActorPosition(void *,s16 *,s16 *);
extern TaskNode *CreateThreeStageProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern void CreateThreeStageStages(const void *,TaskNode **,u8,TaskNode *);
extern u32 GetThreeStageActorMode(void *);
extern void SetThreeStageProjectedMode(TaskNode *,u8);
extern TaskNode *CreateThreeStageAuxiliary(const void *,u8,u16,u16,TaskNode *);
extern u32 CountThreeStageTargets(void *,u8,u16,TaskNode *);
extern u32 PollThreeStageChildren(TaskNode **,u32);
extern void *GetThreeStageTarget(void *,u8);
extern u32 ThreeStageTargetChild(TaskNode *,struct ThreeStageEvent *,void *);
extern TaskNode *CreateThreeStageTask(u32 (*)(TaskNode *,struct ThreeStageEvent *,void *),u32,struct ThreeStageEvent *,TaskNode *);
extern u32 PollThreeStageStages(TaskNode **,u8);
extern TaskNode *PollThreeStageProjected(TaskNode *);
extern u32 IsThreeStageActorFinished(void *);

u32 AdvanceThreeStageActorTargetSequence(TaskNode *,struct ThreeStageEvent *,struct ThreeStageWork *)
    __asm__("OriginalActionCallback_000F6A40");
u32 AdvanceThreeStageActorTargetSequence(TaskNode *task,struct ThreeStageEvent *event,
                                        struct ThreeStageWork *work)
{
    s16 x,y;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=3;
        if(work->variant!=0) count=0;
        work->initial=CreateThreeStageInitial(work->record,(const void *)0x0839B904,count,0,0,task);
        break;
    }
    case 1:
        CleanupThreeStageInputs();
        break;
    case 256:
        work->initial=PollThreeStageInitial(work->initial);
        if(work->initial!=0) break;
        if(work->variant!=0) {
            work->count=CountThreeStageDirectTargets(work->record);
            work->delay=1;
            event->phase=258;
            break;
        }
        work->actor_sequence=CreateThreeStageActorSequence(work->record,&work->actor,148,1,
                                      &work->actor_ready,(const void *)0x0839B9E4,0,0,task);
        event->phase++;
        break;
    case 257:
        if(work->actor_ready==0) break;
        ProjectThreeStageActorPosition(work->actor,&x,&y);
        work->projected=CreateThreeStageProjected(x,y,0,1,3,&work->resources[0],
                                                 (const void *)0x0839B928,task);
        CreateThreeStageStages((const void *)0x0839B9B8,&work->stages[0],3,task);
        if((s8)GetThreeStageActorMode(work->actor)>1)
            SetThreeStageProjectedMode(work->projected,1);
        work->stage=CreateThreeStageAuxiliary((const void *)0x0839B9E8,1,4,0,task);
        work->count=CountThreeStageTargets(work->record,0,56,task);
        if(work->count==0) {
            event->phase=259;
            break;
        }
        work->delay=21;
        event->phase++;
        break;
    case 258: {
        struct ThreeStageEvent child_event;
        TaskNode **children;
        TaskNode *child;
        children=&work->children[0];
        PollThreeStageChildren(children,4);
        work->delay--;
        if(work->delay!=0) break;
        child_event.definition=work->ordinal;
        child_event.record=GetThreeStageTarget(work->record,(u8)work->ordinal);
        child=CreateThreeStageTask(ThreeStageTargetChild,40,&child_event,task);
        children[work->ordinal]=child;
        work->delay=30;
        work->ordinal++;
        if(work->ordinal==work->count) event->phase++;
        break;
    }
    case 259:
        if((u8)PollThreeStageStages(&work->stages[0],3)==0) break;
        work->projected=PollThreeStageProjected(work->projected);
        if(work->projected!=0) break;
        if((u8)IsThreeStageActorFinished(work->actor)==0) break;
        if((u8)PollThreeStageChildren(&work->children[0],4)!=0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateThreeStageInitial\n.thumb_set CreateThreeStageInitial,0x080e03f9");
__asm__(".global CleanupThreeStageInputs\n.thumb_set CleanupThreeStageInputs,0x080d38b5");
__asm__(".global PollThreeStageInitial\n.thumb_set PollThreeStageInitial,0x080e05dd");
__asm__(".global CountThreeStageDirectTargets\n.thumb_set CountThreeStageDirectTargets,0x080dd495");
__asm__(".global CreateThreeStageActorSequence\n.thumb_set CreateThreeStageActorSequence,0x080ddf69");
__asm__(".global ProjectThreeStageActorPosition\n.thumb_set ProjectThreeStageActorPosition,0x080dbdc9");
__asm__(".global CreateThreeStageProjected\n.thumb_set CreateThreeStageProjected,0x080d6099");
__asm__(".global CreateThreeStageStages\n.thumb_set CreateThreeStageStages,0x080d4871");
__asm__(".global GetThreeStageActorMode\n.thumb_set GetThreeStageActorMode,0x080dbc89");
__asm__(".global SetThreeStageProjectedMode\n.thumb_set SetThreeStageProjectedMode,0x080d6195");
__asm__(".global CreateThreeStageAuxiliary\n.thumb_set CreateThreeStageAuxiliary,0x080dfd8d");
__asm__(".global CountThreeStageTargets\n.thumb_set CountThreeStageTargets,0x080d8925");
__asm__(".global PollThreeStageChildren\n.thumb_set PollThreeStageChildren,0x080e0571");
__asm__(".global GetThreeStageTarget\n.thumb_set GetThreeStageTarget,0x080dd4a5");
__asm__(".global ThreeStageTargetChild\n.thumb_set ThreeStageTargetChild,0x080f695d");
__asm__(".global CreateThreeStageTask\n.thumb_set CreateThreeStageTask,0x08005b6d");
__asm__(".global PollThreeStageStages\n.thumb_set PollThreeStageStages,0x080d48dd");
__asm__(".global PollThreeStageProjected\n.thumb_set PollThreeStageProjected,0x080d6135");
__asm__(".global IsThreeStageActorFinished\n.thumb_set IsThreeStageActorFinished,0x080de1f1");
__asm__(".balign 4,0");
