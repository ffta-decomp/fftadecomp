#include "../../../src/task_tree_core.h"

typedef signed short s16;

struct DefinitionClearingEvent {
    u16 state;
    u16 unknown_02;
    void *record;
    void *source_record;
    u32 unknown_0c[2];
    u16 type;
    u16 subtype;
    u16 unknown_18;
    u16 unknown_1a;
};
struct DefinitionClearingState {
    u16 delay;
    u8 type;
    u8 completion_ready;
    u8 subtype;
    u8 unknown_05;
    s16 screen_x;
    s16 screen_y;
    u8 unknown_0a[14];
    void *record;
    TaskNode *pending_task;
    TaskNode *setup_task;
    void *source_record;
};
typedef char DefinitionClearingEventMustBe28Bytes[
    sizeof(struct DefinitionClearingEvent) == 28 ? 1 : -1];
typedef char DefinitionClearingStateMustBe40Bytes[
    sizeof(struct DefinitionClearingState) == 40 ? 1 : -1];

extern void ApplyDefinitionRecordCurrentValue(void *,u16);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern void ProjectDefinitionRecordPosition(const void *,s16 *,s16 *);
extern TaskNode *PollAndReleaseDefinitionMotion(TaskNode *);
extern u32 PollDefinitionRecordHandles(void *);
extern void ApplyDefinitionRecordTransition(void *,u16,u16);
extern void CopyOrFillHalfwords(const void *,void *,u32);
extern void CopyOrFillFastWords(const void *,void *,u32);
extern const void *const gClearingStageDefinitions[];
extern const u8 gClearingStageCounts[];
extern u8 gDefinitionShadows[];
extern u8 gDefinitionTileTail[];

u32 AdvanceDefinitionClearingStage(TaskNode *task,
                                  struct DefinitionClearingEvent *event,
                                  struct DefinitionClearingState *payload)
{
    switch (event->state) {
    case 0:
        payload->type = event->type;
        payload->subtype = event->subtype;
        payload->record = event->record;
        payload->source_record = event->source_record;
        break;
    case 256:
        if (payload->subtype == 0) {
            ApplyDefinitionRecordCurrentValue(payload->record,60);
            payload->setup_task = CreateDefinitionStageTask(
                gClearingStageDefinitions[payload->subtype],
                gClearingStageCounts[payload->subtype],4,0,task);
        }
        event->state++;
        break;
    case 257:
        if (payload->delay != 0)
            payload->delay--;
        if (payload->delay != 0)
            break;
        if (payload->pending_task != 0 && payload->completion_ready == 0)
            break;
        ProjectDefinitionRecordPosition(payload->record,
                                         &payload->screen_x,&payload->screen_y);
        event->state++;
        break;
    case 258: {
        TaskNode *pending_task = PollAndReleaseDefinitionMotion(payload->pending_task);
        payload->pending_task = pending_task;
        if (pending_task == 0 && (u8)PollDefinitionRecordHandles(payload->record) != 0) {
            u16 palette_zero;
            u16 object_zero;
            u32 tile_zero;
            register u8 *destination asm("r1");
            register u8 *shadow asm("r4");
            if (payload->subtype == 0)
                ApplyDefinitionRecordTransition(payload->record,0,0);
            /* These are distinct native fill source objects and widths. */
            palette_zero = (u32)pending_task;
            shadow = gDefinitionShadows;
            destination = shadow;
            /* Retain the initialized destination before the control literal. */
            asm("" : : "r" (destination));
            CopyOrFillHalfwords(&palette_zero,destination,0x01000040);
            object_zero = (u32)pending_task;
            /* The original base survives the first fill and is then advanced. */
            asm("" : : "r" (shadow));
            shadow += 512;
            /* Keep the updated native base distinct from its argument copy. */
            asm("" : : "r" (shadow));
            destination = shadow;
            asm("" : : "r" (destination));
            CopyOrFillHalfwords(&object_zero,destination,0x01000070);
            tile_zero = (u32)pending_task;
            CopyOrFillFastWords(&tile_zero,gDefinitionTileTail,0x01000010);
            event->state = 2;
        }
        break;
    }
    }
    return 0;
}

asm(".global ApplyDefinitionRecordCurrentValue\n.thumb_set ApplyDefinitionRecordCurrentValue,0x080DE10D\n"
    ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080DFD8D\n"
    ".global ProjectDefinitionRecordPosition\n.thumb_set ProjectDefinitionRecordPosition,0x080DBDC9\n"
    ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x080DBA5D\n"
    ".global PollDefinitionRecordHandles\n.thumb_set PollDefinitionRecordHandles,0x080DE1F1\n"
    ".global ApplyDefinitionRecordTransition\n.thumb_set ApplyDefinitionRecordTransition,0x080DE151\n"
    ".global CopyOrFillHalfwords\n.thumb_set CopyOrFillHalfwords,0x0814186D\n"
    ".global CopyOrFillFastWords\n.thumb_set CopyOrFillFastWords,0x08141869\n"
    ".global gClearingStageDefinitions\n.set gClearingStageDefinitions,0x08395B94\n"
    ".global gClearingStageCounts\n.set gClearingStageCounts,0x08395B98\n"
    ".global gDefinitionShadows\n.set gDefinitionShadows,0x03003920\n"
    ".global gDefinitionTileTail\n.set gDefinitionTileTail,0x0600FFC0\n");
