typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct SequenceEvent {
    u16 state;
    u16 unknown02;
    void *record;
    u8 unknown08[12];
    u16 x;
    u16 y;
    u32 unknown24;
};
struct SequenceParentWork {
    u16 x;
    u16 y;
    u8 flag;
    u8 unknown05[3];
    struct TaskNode *first_child;
    struct TaskNode *second_child;
    struct TaskNode *third_child;
    struct TaskNode *definition;
    void *record;
    struct TaskNode *record_effect;
    struct TaskNode *timer;
};
typedef u32 (*SequenceCallback)(struct TaskNode *, struct SequenceEvent *, void *);

#define RETAIL_ALIAS(name, address) \
    __asm__(".global " #name "\n.thumb_set " #name ", " address "\n")
RETAIL_ALIAS(CreateDefinitionEffect, "0x080e03f9");
RETAIL_ALIAS(ReadCurrentCoordinates, "0x0801e6f1");
RETAIL_ALIAS(ResetSequenceDisplay, "0x080d38b5");
RETAIL_ALIAS(PollDefinitionEffect, "0x080e05dd");
RETAIL_ALIAS(CreateSequenceTimer, "0x080dfd69");
RETAIL_ALIAS(PollSequenceTimer, "0x080dfed9");
RETAIL_ALIAS(CreateSequenceChild, "0x08005b6d");
RETAIL_ALIAS(AdvanceFirstSequenceChild, "0x0810ea79");
RETAIL_ALIAS(AdvanceSecondSequenceChild, "0x0810ef0d");
RETAIL_ALIAS(AdvanceThirdSequenceChild, "0x0810faf9");
RETAIL_ALIAS(PollSequenceChild, "0x080e051d");
RETAIL_ALIAS(CreateRecordEffect, "0x08115ae5");
RETAIL_ALIAS(PollRecordEffect, "0x08115b41");
/* This call provides full-word 0/8 in R2; the retail callee captures LOW8. */
extern struct TaskNode *CreateDefinitionEffect(void *, const void *, u32, u8,
                                              const void *, struct TaskNode *);
extern void ReadCurrentCoordinates(u16 *, u16 *);
extern void ResetSequenceDisplay(void);
extern struct TaskNode *PollDefinitionEffect(struct TaskNode *);
extern struct TaskNode *CreateSequenceTimer(u8, u16, struct TaskNode *);
extern struct TaskNode *PollSequenceTimer(struct TaskNode *);
extern struct TaskNode *CreateSequenceChild(SequenceCallback, u16,
                                           const struct SequenceEvent *,
                                           struct TaskNode *);
extern u32 AdvanceFirstSequenceChild(struct TaskNode *, struct SequenceEvent *, void *);
extern u32 AdvanceSecondSequenceChild(struct TaskNode *, struct SequenceEvent *, void *);
extern u32 AdvanceThirdSequenceChild(struct TaskNode *, struct SequenceEvent *, void *);
extern struct TaskNode *PollSequenceChild(struct TaskNode *);
extern struct TaskNode *CreateRecordEffect(void *, u32, struct TaskNode *);
extern struct TaskNode *PollRecordEffect(struct TaskNode *);

u32 AdvanceAuthoredSequenceParent(struct TaskNode *parent,
                                 struct SequenceEvent *event,
                                 struct SequenceParentWork *work)
{
    /* Retail initializes only the template fields consumed by each child. */
    struct SequenceEvent first_event;
    struct SequenceEvent second_event;
    struct SequenceEvent third_event;

    switch (event->state) {
    case 0:
    {
        u16 input_flag = event->y;
        void *record;
        u32 count;
        work->flag = input_flag;
        record = event->record;
        work->record = record;
        count = 8;
        if ((u8)input_flag != 0)
            count = 0;
        work->definition = CreateDefinitionEffect(record, (const void *)0x083a2d64,
                                                  count, 7, 0, parent);
        ReadCurrentCoordinates(&work->x, &work->y);
        break;
    }
    case 1:
        ResetSequenceDisplay();
        break;
    case 256:
        /* The branch consumes the flag before the callback can mutate it. */
        if (work->flag != 0) {
            work->definition = PollDefinitionEffect(work->definition);
            if (work->definition == 0)
                event->state = 260;
        } else {
            work->definition = PollDefinitionEffect(work->definition);
            if (work->definition == 0) {
                work->timer = CreateSequenceTimer(1, 30, parent);
                ++event->state;
            }
        }
        break;
    case 257:
        work->timer = PollSequenceTimer(work->timer);
        if (work->timer != 0)
            break;
        work->first_child = CreateSequenceChild(AdvanceFirstSequenceChild, 20,
                                                &first_event, parent);
        ++event->state;
        break;
    case 258:
        work->first_child = PollSequenceChild(work->first_child);
        if (work->first_child != 0)
            break;
        second_event.record = work->record;
        work->second_child = CreateSequenceChild(AdvanceSecondSequenceChild, 488,
                                                 &second_event, parent);
        ++event->state;
        /* The newly created second child is polled in this invocation. */
    case 259:
        work->second_child = PollSequenceChild(work->second_child);
        if (work->second_child == 0)
            ++event->state;
        break;
    case 260:
        third_event.x = work->x;
        third_event.y = work->y;
        third_event.record = work->record;
        work->third_child = CreateSequenceChild(AdvanceThirdSequenceChild, 344,
                                                &third_event, parent);
        ++event->state;
        break;
    case 261:
        work->third_child = PollSequenceChild(work->third_child);
        if (work->third_child != 0)
            break;
        work->record_effect = CreateRecordEffect(work->record, 0, parent);
        ++event->state;
        break;
    case 262:
        work->record_effect = PollRecordEffect(work->record_effect);
        if (work->record_effect == 0)
            event->state = 2;
        break;
    }
    return 0;
}
