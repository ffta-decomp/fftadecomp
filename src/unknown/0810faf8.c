#include "ffta/unsigned_types.h"
typedef signed short s16;
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
struct TransitionWork {
    u16 countdown;
    u16 x;
    u16 y;
    u16 unknown06;
    struct TaskNode *definition;
    void *record;
    u32 unknown16;
    struct TaskNode *timer;
};

#define RETAIL_ALIAS(name, address) \
    __asm__(".global " #name "\n.thumb_set " #name ", " address "\n")
RETAIL_ALIAS(SetSequenceRecord, "0x0801e2a5");
RETAIL_ALIAS(ReadSequenceMaskIndices, "0x0801e611");
RETAIL_ALIAS(GetDisplayMask, "0x080035a9");
RETAIL_ALIAS(SetSequenceCoordinates, "0x0801e5e1");
RETAIL_ALIAS(CommitSequenceCoordinates, "0x0801b879");
RETAIL_ALIAS(ReadRecordView, "0x08115acd");
RETAIL_ALIAS(GetRecordViewData, "0x080d3905");
RETAIL_ALIAS(ApplySequenceRegion, "0x0801dcb9");
RETAIL_ALIAS(CreateSequenceDefinition, "0x080d3e9d");
RETAIL_ALIAS(PollSequenceDefinition, "0x080d3f09");
RETAIL_ALIAS(CreateSequenceTimer, "0x080dfd69");
RETAIL_ALIAS(PollSequenceTimer, "0x080dfed9");
extern void SetSequenceRecord(void *);
extern void ReadSequenceMaskIndices(u8 *, u8 *);
extern u32 GetDisplayMask(u8);
extern void SetSequenceCoordinates(s16, s16);
extern void CommitSequenceCoordinates(void);
extern u32 ReadRecordView(void *);
extern u8 *GetRecordViewData(u32);
extern void ApplySequenceRegion(u8 *);
extern struct TaskNode *CreateSequenceDefinition(const void *, struct TaskNode *);
extern struct TaskNode *PollSequenceDefinition(struct TaskNode *);
extern struct TaskNode *CreateSequenceTimer(u8, u16, struct TaskNode *);
extern struct TaskNode *PollSequenceTimer(struct TaskNode *);

/* The fixed definition and phase order belong to this authored sequence. */
u32 AdvanceAuthoredTransitionSequence(struct TaskNode *parent,
                                     struct SequenceEvent *event,
                                     struct TransitionWork *work)
{
    u8 first_index;
    u8 second_index;
    register u32 mask __asm__("r0");

    switch (event->state) {
    case 0:
        work->x = event->x;
        work->y = event->y;
        work->record = event->record;
        SetSequenceRecord(work->record);
        ReadSequenceMaskIndices(&first_index, &second_index);
        mask = GetDisplayMask(first_index);
        __asm__("" : "+r"(mask));
        {
            register u32 control __asm__("r1") = *(u16 *)0x03000940;
            __asm__("" : "+r"(control));
            control |= mask;
            __asm__("" : "+r"(control));
            *(u16 *)0x03000940 = control;
        }
        mask = GetDisplayMask(second_index);
        __asm__("" : "+r"(mask));
        {
            register u32 control __asm__("r1") = *(u16 *)0x03000940;
            __asm__("" : "+r"(control));
            control |= mask;
            __asm__("" : "+r"(control));
            *(u16 *)0x03000940 = control;
        }
        work->countdown = 30;
        break;
    case 256:
        --work->countdown;
        if (work->countdown != 0)
            break;
        SetSequenceCoordinates((s16)work->x, (s16)work->y);
        CommitSequenceCoordinates();
        ApplySequenceRegion(GetRecordViewData(ReadRecordView(work->record)) + 192);
        ++event->state;
        break;
    case 257:
        work->definition = CreateSequenceDefinition((const void *)0x083a2df4,
                                                    parent);
        work->timer = CreateSequenceTimer(0, 30, parent);
        ++event->state;
        break;
    case 258:
        work->timer = PollSequenceTimer(work->timer);
        if (work->timer != 0)
            break;
        work->definition = PollSequenceDefinition(work->definition);
        if (work->definition != 0)
            break;
        mask = GetDisplayMask(3);
        __asm__("" : "+r"(mask));
        {
            register u32 control __asm__("r1") = *(u16 *)0x03000940;
            __asm__("" : "+r"(control));
            control &= ~mask;
            __asm__("" : "+r"(control));
            *(u16 *)0x03000940 = control;
        }
        event->state = 2;
        break;
    }
    return 0;
}
