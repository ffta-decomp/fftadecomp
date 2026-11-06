typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
struct NotifiedActionEvent {
    u16 phase;
    u8 unknown02[2];
    void *record;
    u8 unknown08[12];
    u16 definition;
    u16 variant;
    u8 unknown18[4];
};
struct NotifiedActionWork {
    u8 variant, complete;
    u8 unknown02[2];
    void *actor;
    u32 unknown08;
    void *record;
    TaskNode *initial;
    TaskNode *child;
    TaskNode *sequence;
};
typedef char NotifiedEventMustBe28[sizeof(struct NotifiedActionEvent)==28?1:-1];
typedef char NotifiedWorkMustBe28[sizeof(struct NotifiedActionWork)==28?1:-1];
extern TaskNode *CreateNotifiedInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupNotifiedInputs(void);
extern TaskNode *PollNotifiedInitial(TaskNode *);
extern u32 IsNotifiedRecordBlocked(void *);
extern TaskNode *CreateNotifiedActorSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern u32 IsNotifiedTargetEligible(void *,u8);
extern u32 Definition84VariantChild(TaskNode *,struct NotifiedActionEvent *,void *);
extern TaskNode *CreateNotifiedTask(u32 (*)(TaskNode *,struct NotifiedActionEvent *,void *),u32,struct NotifiedActionEvent *,TaskNode *);
extern TaskNode *PollNotifiedChild(TaskNode *);

u32 AdvanceNotifiedActorActionChild(TaskNode *,struct NotifiedActionEvent *,struct NotifiedActionWork *)
    __asm__("OriginalActionCallback_000F3E7C");
u32 AdvanceNotifiedActorActionChild(TaskNode *task,struct NotifiedActionEvent *event,
                                  struct NotifiedActionWork *work)
{
    struct NotifiedActionEvent child_event;
    switch(event->phase) {
    case 0: {
        u8 count;
        work->variant=event->variant;
        work->record=event->record;
        count=3;
        if(work->variant!=0) count=0;
        work->initial=CreateNotifiedInitial(work->record,(const void *)0x0839AF04,count,0,0,task);
        break;
    }
    case 1:
        CleanupNotifiedInputs();
        break;
    case 256: {
        u8 blocked;
        work->initial=PollNotifiedInitial(work->initial);
        if(work->initial!=0) break;
        blocked=IsNotifiedRecordBlocked(work->record);
        if(blocked!=0) {
            event->phase=2;
            break;
        }
        work->sequence=CreateNotifiedActorSequence(work->record,&work->actor,0x8007,2,
                                                   &work->complete,(const void *)0x0839AF28,
                                                   5,blocked,task);
        event->phase++;
        break;
    }
    case 257:
        if(work->complete==0) break;
        if((u8)IsNotifiedTargetEligible(work->record,0)==0) {
            event->phase=2;
            break;
        }
        child_event.definition=84;
        child_event.variant=1;
        child_event.record=work->record;
        work->child=CreateNotifiedTask(Definition84VariantChild,68,&child_event,task);
        event->phase++;
        break;
    case 258:
        work->child=PollNotifiedChild(work->child);
        if(work->child==0) event->phase=2;
        break;
    }
    return 0;
}

__asm__(".global CreateNotifiedInitial\n.thumb_set CreateNotifiedInitial,0x080e03f9");
__asm__(".global CleanupNotifiedInputs\n.thumb_set CleanupNotifiedInputs,0x080d38b5");
__asm__(".global PollNotifiedInitial\n.thumb_set PollNotifiedInitial,0x080e05dd");
__asm__(".global IsNotifiedRecordBlocked\n.thumb_set IsNotifiedRecordBlocked,0x080d3b55");
__asm__(".global CreateNotifiedActorSequence\n.thumb_set CreateNotifiedActorSequence,0x080ddf69");
__asm__(".global IsNotifiedTargetEligible\n.thumb_set IsNotifiedTargetEligible,0x080d8859");
__asm__(".global Definition84VariantChild\n.thumb_set Definition84VariantChild,0x080e9e29");
__asm__(".global CreateNotifiedTask\n.thumb_set CreateNotifiedTask,0x08005b6d");
__asm__(".global PollNotifiedChild\n.thumb_set PollNotifiedChild,0x080e051d");
/* The complete original owns zero fill up to the next four-byte entry. */
__asm__(".balign 4,0");
