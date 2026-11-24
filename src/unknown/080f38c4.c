#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef signed int s32;
typedef struct TaskNode TaskNode;

struct VariantActionEvent {
    u16 phase;
    u8 unknown02[2];
    void *record;
    u8 unknown08[12];
    s16 definition;
    u16 variant;
    u8 unknown18[4];
};
struct VariantActionWork {
    s16 x, y;
    u8 mode, variant;
    u8 unknown06[2];
    void *first_actor;
    void *target;
    TaskNode *child;
    void *record;
    TaskNode *initial;
    void *resources[4];
    TaskNode *projected;
    TaskNode *auxiliary;
    TaskNode *sequence;
    TaskNode *motion;
    TaskNode *stage;
};
typedef char VariantEventMustBe28[sizeof(struct VariantActionEvent)==28?1:-1];
typedef char VariantWorkMustBe64[sizeof(struct VariantActionWork)==64?1:-1];

extern TaskNode *CreateVariantInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupVariantInputs(void);
extern TaskNode *PollVariantInitial(TaskNode *);
extern void StartVariantCue(const void *,u8,u8,u8,u8);
extern u32 IsVariantRecordBlocked(void *);
extern void *GetVariantFirstActor(void *);
extern u32 IsVariantTargetEligible(void *,u8);
extern void TouchVariantTarget(void *,u8);
extern u32 IsVariantActionBusy(void);
extern void *GetVariantTargetCell(void *,u8);
extern void *ProjectVariantCell(void *,s16 *,s16 *,u8);
extern void StartVariantPositionCue(const void *,u8,u8,s32,s32,u32);
/* Distinct original sequence objects, whose addresses are independent literals. */
extern const u8 VariantSequenceNear[] __asm__("0x08949D48");
extern const u8 VariantSequenceFar[] __asm__("0x08949FC0");
extern TaskNode *CreateVariantSequence(const void *,TaskNode *);
extern TaskNode *CreateVariantAuxiliary(const void *,TaskNode *);
extern TaskNode *CreateVariantProjected(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateVariantMotion(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern u32 VariantRecordChild(TaskNode *,struct VariantActionEvent *,void *);
extern TaskNode *CreateVariantTask(u32 (*)(TaskNode *,struct VariantActionEvent *,void *),u32,struct VariantActionEvent *,TaskNode *);
extern TaskNode *CreateVariantStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollVariantProjected(TaskNode *);
extern TaskNode *PollVariantAuxiliary(TaskNode *);
extern TaskNode *PollVariantSequence(TaskNode *);
extern u32 GetVariantDisplayMask(u32);
extern TaskNode *PollVariantMotion(TaskNode *);

u32 AdvanceVariantActorActionSequence(TaskNode *,struct VariantActionEvent *,struct VariantActionWork *)
    __asm__("OriginalActionCallback_000F38C4");
u32 AdvanceVariantActorActionSequence(TaskNode *task,struct VariantActionEvent *event,
                                    struct VariantActionWork *work)
{
    struct VariantActionEvent child_event;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        switch(event->definition) {
        case 81: work->mode=0; break;
        case 134: work->mode=1; break;
        case 112: work->mode=2; break;
        case 174: work->mode=3; break;
        }
        count=5;
        if(work->variant!=0) count=0;
        work->initial=CreateVariantInitial(work->record,(const void *)0x0839AC1C,
                                           count,7,0,task);
        break;
    }
    case 1:
        CleanupVariantInputs();
        break;
    case 256:
        work->initial=PollVariantInitial(work->initial);
        if(work->initial!=0) break;
        if(work->mode>1) StartVariantCue((const void *)0x088EA990,6,1,1,1);
        if((u8)IsVariantRecordBlocked(work->record)!=0) {
            event->phase=2;
            break;
        }
        work->first_actor=GetVariantFirstActor(work->record);
        if((u8)IsVariantTargetEligible(work->record,0)==0) {
            event->phase=2;
            break;
        }
        TouchVariantTarget(work->record,0);
        event->phase++;
        break;
    case 257: {
        u8 busy;
        void *cell;
        const void *sequence;
        busy=IsVariantActionBusy();
        if(busy!=0) break;
        cell=GetVariantTargetCell(work->record,0);
        work->target=ProjectVariantCell(cell,&work->x,&work->y,0);
        StartVariantPositionCue((const void *)0x088F46F0,0,2,work->x,
                                 (s16)((u16)work->y-4),busy);
        if(work->mode<=1) {
            sequence=VariantSequenceNear;
            /* Original branch defines this complete first-argument pointer. */
            __asm__("" : "+r"(sequence));
        } else {
            sequence=VariantSequenceFar;
            __asm__("" : "+r"(sequence));
        }
        work->sequence=CreateVariantSequence(sequence,task);
        work->auxiliary=CreateVariantAuxiliary((const void *)0x0894D69C,task);
        work->projected=CreateVariantProjected(work->x,work->y,0,1,4,
                                               work->resources,(const void *)0x0839AC58,task);
        if(work->mode<=1) {
            work->motion=CreateVariantMotion(cell,(const void *)0x0839ACD0,12,41,4,task,80);
        } else {
            /* The constructor receives only this field from the partial event. */
            child_event.record=work->record;
            work->child=CreateVariantTask(VariantRecordChild,32,&child_event,task);
        }
        work->stage=CreateVariantStage((const void *)0x0839AD00,1,4,0,task);
        event->phase++;
        break;
    }
    case 258: {
        u32 mask;
        work->projected=PollVariantProjected(work->projected);
        if(work->projected!=0) break;
        work->auxiliary=PollVariantAuxiliary(work->auxiliary);
        if(work->auxiliary!=0) break;
        work->sequence=PollVariantSequence(work->sequence);
        if(work->sequence!=0) break;
        mask=GetVariantDisplayMask(2);
        *(u16 *)0x03000940 &= ~mask;
        work->motion=PollVariantMotion(work->motion);
        if(work->motion!=0) break;
        work->child=PollVariantInitial(work->child);
        if(work->child==0) event->phase=2;
        break;
    }
    }
    return 0;
}

__asm__(".global CreateVariantInitial\n.thumb_set CreateVariantInitial,0x080e03f9");
__asm__(".global CleanupVariantInputs\n.thumb_set CleanupVariantInputs,0x080d38b5");
__asm__(".global PollVariantInitial\n.thumb_set PollVariantInitial,0x080e05dd");
__asm__(".global StartVariantCue\n.thumb_set StartVariantCue,0x080d45d1");
__asm__(".global IsVariantRecordBlocked\n.thumb_set IsVariantRecordBlocked,0x080d3b55");
__asm__(".global GetVariantFirstActor\n.thumb_set GetVariantFirstActor,0x080dd47d");
__asm__(".global IsVariantTargetEligible\n.thumb_set IsVariantTargetEligible,0x080d8859");
__asm__(".global TouchVariantTarget\n.thumb_set TouchVariantTarget,0x080dbffd");
__asm__(".global IsVariantActionBusy\n.thumb_set IsVariantActionBusy,0x080d8b4d");
__asm__(".global GetVariantTargetCell\n.thumb_set GetVariantTargetCell,0x080dd4a5");
__asm__(".global ProjectVariantCell\n.thumb_set ProjectVariantCell,0x080dd749");
__asm__(".global StartVariantPositionCue\n.thumb_set StartVariantPositionCue,0x080d7221");
__asm__(".global CreateVariantSequence\n.thumb_set CreateVariantSequence,0x080d4705");
__asm__(".global CreateVariantAuxiliary\n.thumb_set CreateVariantAuxiliary,0x080d3e9d");
__asm__(".global CreateVariantProjected\n.thumb_set CreateVariantProjected,0x080d6099");
__asm__(".global CreateVariantMotion\n.thumb_set CreateVariantMotion,0x080dcfe5");
__asm__(".global VariantRecordChild\n.thumb_set VariantRecordChild,0x080f378d");
__asm__(".global CreateVariantTask\n.thumb_set CreateVariantTask,0x08005b6d");
__asm__(".global CreateVariantStage\n.thumb_set CreateVariantStage,0x080dfd8d");
__asm__(".global PollVariantProjected\n.thumb_set PollVariantProjected,0x080d6135");
__asm__(".global PollVariantAuxiliary\n.thumb_set PollVariantAuxiliary,0x080d3f09");
__asm__(".global PollVariantSequence\n.thumb_set PollVariantSequence,0x080d4775");
__asm__(".global GetVariantDisplayMask\n.thumb_set GetVariantDisplayMask,0x080035a9");
__asm__(".global PollVariantMotion\n.thumb_set PollVariantMotion,0x080dba5d");
