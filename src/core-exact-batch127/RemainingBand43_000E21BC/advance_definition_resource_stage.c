#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;
struct DefinitionResourceHeader;
struct DefinitionResourceEvent {
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
struct DefinitionResourceState {
    u16 unknown_00;
    u8 type;
    u8 completion_ready;
    u8 subtype;
    u8 unknown_05;
    s16 screen_x;
    s16 screen_y;
    u16 unknown_0a;
    void *record;
    u32 unknown_10[2];
    TaskNode *position_task;
    void *resource;
    TaskNode *auxiliary_task;
    TaskNode *palette_task;
    TaskNode *record_task;
    TaskNode *setup_task;
    void *source_record;
};
typedef char DefinitionResourceEventMustBe28Bytes[
    sizeof(struct DefinitionResourceEvent) == 28 ? 1 : -1];
typedef char DefinitionResourceStateMustBe52Bytes[
    sizeof(struct DefinitionResourceState) == 52 ? 1 : -1];
extern void ApplyDefinitionRecordCurrentValue(void *,u16);
extern TaskNode *CreateDefinitionRecordTask(void *,u8 *,u8,s8,u8,u8,u16,TaskNode *);
extern void ProjectDefinitionRecordPosition(const void *,s16 *,s16 *);
extern void ConfigureDefinitionResourceCoordinates(u8,u8,u16,s16,s16);
extern void *CreateDefinitionResource(u8,const struct DefinitionResourceHeader *,u16,u8);
extern u32 ReadDefinitionDisplayMask(u8);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
/* This caller supplies signed coordinates; the entry stores their low halves. */
extern TaskNode *CreatePositionedDefinitionTaskAtPoint(s16,s16,int,u8,u32,
                                                      void *,const void *,TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern void *PollAndReleaseDefinitionResource(void *,u8);
extern TaskNode *PollAndReleaseDefinitionAuxiliary(TaskNode *);
extern TaskNode *PollAndReleaseDefinitionPalette(TaskNode *);
extern TaskNode *PollAndReleasePositionedDefinitionTask(TaskNode *);
extern TaskNode *PollAndReleaseDefinitionMotion(TaskNode *);
extern void CopyOrFillHalfwords(const void *,void *,u32);
extern void CopyOrFillFastWords(const void *,void *,u32);
extern const struct DefinitionResourceHeader gDefinitionResourceRecord;
extern const u8 gDefinitionAuxiliarySequence[];
extern const u8 gDefinitionPaletteSequence[];
extern const u8 gDefinitionPositionCounts[];
extern const void *const gDefinitionPositionSequences[];
extern const u8 gDefinitionSetupSequence[];
extern u16 gDefinitionDisplayShadow;
extern u8 gDefinitionShadows[];
extern u8 gDefinitionTileTail[];

u32 AdvanceDefinitionResourceStage(TaskNode *task,
                                  struct DefinitionResourceEvent *event,
                                  struct DefinitionResourceState *payload)
{
    switch (event->state) {
    case 0:
        payload->type = event->type;
        payload->subtype = event->subtype;
        payload->record = event->record;
        payload->source_record = event->source_record;
        break;
    case 256: {
        u8 countdown = 50;
        ApplyDefinitionRecordCurrentValue(payload->record,60);
        payload->record_task = CreateDefinitionRecordTask(
            payload->record,&payload->completion_ready,1,-1,0,countdown,0,task);
        event->state++;
        break;
    }
    case 257: {
        u32 display_mask;
        u16 display_value;
        if (payload->record_task != 0 && payload->completion_ready == 0)
            break;
        ProjectDefinitionRecordPosition(payload->record,
                                         &payload->screen_x,&payload->screen_y);
        ConfigureDefinitionResourceCoordinates(0,2,0,payload->screen_x,
                                                (s16)((u16)payload->screen_y-32));
        payload->resource = CreateDefinitionResource(0,&gDefinitionResourceRecord,0x3cf,6);
        display_mask = ReadDefinitionDisplayMask(2);
        display_value = gDefinitionDisplayShadow;
        display_value |= display_mask;
        gDefinitionDisplayShadow = display_value;
        payload->auxiliary_task = CreateDefinitionAuxiliaryTask(gDefinitionAuxiliarySequence,task);
        payload->palette_task = CreateDefinitionPaletteTask(gDefinitionPaletteSequence,task);
        payload->position_task = CreatePositionedDefinitionTaskAtPoint(
            payload->screen_x,payload->screen_y,0,1,
            gDefinitionPositionCounts[payload->type],payload->unknown_10,
            gDefinitionPositionSequences[payload->type],task);
        payload->setup_task = CreateDefinitionStageTask(gDefinitionSetupSequence,2,4,0,task);
        event->state++;
        break;
    }
    case 258: {
        u32 display_mask;
        TaskNode *remaining_record;
        u16 palette_zero;
        u16 object_zero;
        u32 tile_zero;
        register u8 *destination asm("r1");
        register u8 *shadow asm("r4");
        payload->resource = PollAndReleaseDefinitionResource(payload->resource,0);
        if (payload->resource != 0)
            break;
        payload->auxiliary_task = PollAndReleaseDefinitionAuxiliary(payload->auxiliary_task);
        if (payload->auxiliary_task != 0)
            break;
        display_mask = ReadDefinitionDisplayMask(2);
        gDefinitionDisplayShadow &= ~display_mask;
        payload->palette_task = PollAndReleaseDefinitionPalette(payload->palette_task);
        if (payload->palette_task != 0)
            break;
        /* Preserve the original unconditional call and its native interface. */
        payload->position_task = PollAndReleasePositionedDefinitionTask(payload->position_task);
        if (payload->position_task != 0)
            break;
        remaining_record = PollAndReleaseDefinitionMotion(payload->record_task);
        payload->record_task = remaining_record;
        if (remaining_record != 0)
            break;
        palette_zero = (u32)remaining_record;
        shadow = gDefinitionShadows;
        destination = shadow;
        /* Retain the initialized native destination before its control literal. */
        asm("" : : "r" (destination));
        CopyOrFillHalfwords(&palette_zero,destination,0x01000040);
        object_zero = (u32)remaining_record;
        asm("" : : "r" (shadow));
        shadow += 512;
        /* The updated base remains distinct from its next argument copy. */
        asm("" : : "r" (shadow));
        destination = shadow;
        asm("" : : "r" (destination));
        CopyOrFillHalfwords(&object_zero,destination,0x01000070);
        tile_zero = (u32)remaining_record;
        CopyOrFillFastWords(&tile_zero,gDefinitionTileTail,0x01000010);
        event->state = 2;
        break;
    }
    }
    return 0;
}

asm(".global ApplyDefinitionRecordCurrentValue\n.thumb_set ApplyDefinitionRecordCurrentValue,0x080DE10D\n"
    ".global CreateDefinitionRecordTask\n.thumb_set CreateDefinitionRecordTask,0x080DE4B1\n"
    ".global ProjectDefinitionRecordPosition\n.thumb_set ProjectDefinitionRecordPosition,0x080DBDC9\n"
    ".global ConfigureDefinitionResourceCoordinates\n.thumb_set ConfigureDefinitionResourceCoordinates,0x080D49FD\n"
    ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x080D4B65\n"
    ".global ReadDefinitionDisplayMask\n.thumb_set ReadDefinitionDisplayMask,0x080035A9\n"
    ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x080D3E9D\n"
    ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x080D4705\n"
    ".global CreatePositionedDefinitionTaskAtPoint\n.thumb_set CreatePositionedDefinitionTaskAtPoint,0x080D6099\n"
    ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080DFD8D\n"
    ".global PollAndReleaseDefinitionResource\n.thumb_set PollAndReleaseDefinitionResource,0x080D4D2D\n"
    ".global PollAndReleaseDefinitionAuxiliary\n.thumb_set PollAndReleaseDefinitionAuxiliary,0x080D3F09\n"
    ".global PollAndReleaseDefinitionPalette\n.thumb_set PollAndReleaseDefinitionPalette,0x080D4775\n"
    ".global PollAndReleasePositionedDefinitionTask\n.thumb_set PollAndReleasePositionedDefinitionTask,0x080D6135\n"
    ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x080DBA5D\n"
    ".global CopyOrFillHalfwords\n.thumb_set CopyOrFillHalfwords,0x0814186D\n"
    ".global CopyOrFillFastWords\n.thumb_set CopyOrFillFastWords,0x08141869\n"
    ".global gDefinitionResourceRecord\n.set gDefinitionResourceRecord,0x088F1870\n"
    ".global gDefinitionAuxiliarySequence\n.set gDefinitionAuxiliarySequence,0x0894D690\n"
    ".global gDefinitionPaletteSequence\n.set gDefinitionPaletteSequence,0x0894C5F0\n"
    ".global gDefinitionPositionCounts\n.set gDefinitionPositionCounts,0x08395AA8\n"
    ".global gDefinitionPositionSequences\n.set gDefinitionPositionSequences,0x08395A4C\n"
    ".global gDefinitionSetupSequence\n.set gDefinitionSetupSequence,0x08395BAC\n"
    ".global gDefinitionDisplayShadow\n.set gDefinitionDisplayShadow,0x03000940\n"
    ".global gDefinitionShadows\n.set gDefinitionShadows,0x03003920\n"
    ".global gDefinitionTileTail\n.set gDefinitionTileTail,0x0600FFC0\n");
