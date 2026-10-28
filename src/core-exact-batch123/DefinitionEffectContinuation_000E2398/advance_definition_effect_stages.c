#include "../../../src/task_tree_core.h"

typedef signed short s16;

struct DefinitionEffectContext {
    u16 state;
    u16 unknown_02;
    void *record;
    u32 parameter;
    u32 flags;
    u32 unknown_10;
    u16 definition_id;
    u16 type_and_flags;
    u16 identifier;
    u16 unknown_1a;
};
struct DefinitionEffectStages {
    u8 type;
    u8 final_stage;
    u8 subtype;
    u8 unknown_03;
    u16 flags;
    u8 unknown_06[10];
    u16 identifier;
    u16 unknown_12;
    TaskNode *final_task;
    void *object;
    TaskNode *initial_task;
    TaskNode *followup_task;
    void *source_record;
};
typedef char DefinitionContextMustBe28Bytes[
    sizeof(struct DefinitionEffectContext) == 28 ? 1 : -1];
typedef char DefinitionStagesMustBe40Bytes[
    sizeof(struct DefinitionEffectStages) == 40 ? 1 : -1];

extern void *GetRecordNestedPointer(void *);
extern void CopyCountedPaletteGroupsToShadow(const u8 *, u32, u32, u32, u32);
extern TaskNode *CreateDefinitionEffectTask(void *, const void *, u8, u8,
                                            const s16 *, TaskNode *);
extern void CleanupDefinitionEffectInputs(void);
extern TaskNode *PollAndReleaseEffectStageTask(TaskNode *);
extern TaskNode *CreateManagedTaskChild(void *, u8, TaskNode *);
extern TaskNode *PollAndReleaseEffectFollowup(TaskNode *);
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback, u16,
                                          const u32 *, TaskNode *);
extern TaskNode *PollAndReleaseDefinitionChild(TaskNode *);
extern const u8 gInitialDefinitionsDefault[];
extern const u8 gInitialDefinitionsFour[];
extern const u8 gInitialDefinitionsSix[];
extern const u8 gInitialDefinitionsSeven[];
extern void *const gFollowupDefinitionsByType[];
extern const u8 gFollowupCountsByType[];
extern const TaskCallback gDefinitionFinalCallbacks[];
extern const u16 gDefinitionFinalPayloadSizes[];
extern const u8 gCommonEffectPalette[];
extern const u8 gParameterEffectPaletteSix[];
extern const u8 gParameterEffectPaletteSeven[];
extern const u8 gEffectPaletteNine[];
extern const u8 gEffectPaletteTwelve[];
extern const u8 gExtraEffectPaletteThirteen[];
extern const u8 gEffectPaletteTwentyOne[];
extern const u8 gDefaultFollowupPalette[];
extern const u8 gFollowupPaletteTwentyOne[];
extern const u8 gFollowupPaletteTwentyTwo[];

u32 AdvanceDefinitionEffectStages(TaskNode *task,
                                 struct DefinitionEffectContext *context,
                                 struct DefinitionEffectStages *payload)
{
    u16 entry_state = context->state;

    switch (entry_state) {
    case 0: {
        u32 copy_followup_palette = 1;
        u32 type_flags = context->type_and_flags;
        const void *initial_definitions;
        u8 definition_count;

        if (type_flags == 0x7fff)
            break;
        payload->final_stage = entry_state;
        if ((type_flags & 0xff) == 16) {
            if (context->flags & 2) {
                type_flags = 0x0208;
            } else {
                u32 subtype = (type_flags & 0x0f00) >> 8;
                if (subtype == 11)
                    type_flags = 17;
                else if (subtype == 13)
                    type_flags = 18;
                if (type_flags & 0x8000)
                    break;
            }
        }
        payload->type = type_flags;
        payload->subtype = (type_flags & 0x0f00) >> 8;
        type_flags &= 0xf000;
        payload->flags = type_flags;
        payload->identifier = context->identifier;
        if (payload->identifier <= 362) {
            void *record = context->record;
            payload->source_record = record;
            payload->object = GetRecordNestedPointer(record);
        } else {
            payload->object = context->record;
        }
        initial_definitions = gInitialDefinitionsDefault;
        definition_count = 2;
        switch (payload->type) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 8: case 10:
            CopyCountedPaletteGroupsToShadow(gCommonEffectPalette, 6, 1, 0, 1);
            break;
        case 6:
            CopyCountedPaletteGroupsToShadow(gParameterEffectPaletteSix,
                6, 1, (u8)(context->parameter - 51), 1);
            break;
        case 7:
            CopyCountedPaletteGroupsToShadow(gParameterEffectPaletteSeven,
                6, 1, (u8)(context->parameter + 110), 1);
            payload->final_stage = 1;
            copy_followup_palette = 0;
            break;
        case 9:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteNine, 6, 1, 0, 1);
            payload->final_stage = 3;
            copy_followup_palette = 0;
            break;
        case 11:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteNine,
                6, 1, payload->subtype, 1);
            payload->final_stage = 1;
            copy_followup_palette = 0;
            break;
        case 12: case 14: case 15:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteTwelve, 6, 1, 1, 1);
            payload->final_stage = 2;
            copy_followup_palette = 0;
            break;
        case 13:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteTwelve, 6, 1, 1, 1);
            CopyCountedPaletteGroupsToShadow(gExtraEffectPaletteThirteen,
                7, 1, 0, 1);
            payload->final_stage = 2;
            copy_followup_palette = 0;
            break;
        case 16:
            initial_definitions = gInitialDefinitionsFour;
            definition_count = 2;
            payload->final_stage = 4;
            copy_followup_palette = 0;
            break;
        case 17:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteTwelve, 6, 1, 1, 1);
            payload->final_stage = 1;
            copy_followup_palette = 0;
            break;
        case 18:
            payload->subtype = 1;
            CopyCountedPaletteGroupsToShadow(gCommonEffectPalette, 6, 1, 0, 1);
            break;
        case 19:
            initial_definitions = gInitialDefinitionsFour;
            definition_count = 2;
            payload->final_stage = 4;
            copy_followup_palette = 0;
            break;
        case 20:
            payload->final_stage = 5;
            copy_followup_palette = 0;
            break;
        case 21:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteTwentyOne, 6, 1, 0, 1);
            initial_definitions = gInitialDefinitionsSix;
            definition_count = 1;
            payload->final_stage = 6;
            break;
        case 22:
            CopyCountedPaletteGroupsToShadow(gEffectPaletteTwentyOne, 6, 1, 6, 1);
            initial_definitions = gInitialDefinitionsSeven;
            definition_count = 1;
            payload->final_stage = 7;
            break;
        }
        if (payload->identifier <= 362)
            payload->initial_task = CreateDefinitionEffectTask(
                payload->source_record, initial_definitions,
                definition_count, 0, 0, task);
        else
            payload->initial_task = CreateDefinitionEffectTask(
                payload->source_record, initial_definitions,
                definition_count, 7, 0, task);
        if (copy_followup_palette) {
            const u8 *palette;
            u32 first_group = 0;
            switch (payload->type) {
            case 21:
                palette = gFollowupPaletteTwentyOne;
                first_group = 1;
                break;
            case 22:
                palette = gFollowupPaletteTwentyTwo;
                break;
            default:
                palette = gDefaultFollowupPalette;
                first_group = payload->subtype;
                break;
            }
            CopyCountedPaletteGroupsToShadow(palette, 6, 0, first_group, 1);
        }
        break;
    }
    case 1:
        CleanupDefinitionEffectInputs();
        break;
    case 256:
        if (payload->object == 0) {
            context->state = 2;
        } else {
            payload->initial_task = PollAndReleaseEffectStageTask(payload->initial_task);
            if (payload->initial_task == 0) {
                void *definitions = gFollowupDefinitionsByType[payload->type];
                if (definitions != 0)
                    payload->followup_task = CreateManagedTaskChild(
                        definitions, gFollowupCountsByType[payload->type], task);
                /* A real callback may have changed this state. */
                context->state++;
            }
        }
        break;
    case 257:
        payload->followup_task = PollAndReleaseEffectFollowup(payload->followup_task);
        if (payload->followup_task == 0) {
            u32 next_event[7];
            /* Only the fields consumed by the selected callback are defined. */
            ((u16 *)next_event)[10] = payload->type;
            ((u16 *)next_event)[11] = payload->subtype;
            ((u16 *)next_event)[12] = 0;
            next_event[1] = (u32)payload->object;
            next_event[2] = (u32)payload->source_record;
            payload->final_task = CreateTaskInCurrentGroup(
                gDefinitionFinalCallbacks[payload->final_stage],
                gDefinitionFinalPayloadSizes[payload->final_stage], next_event, task);
            context->state++;
        }
        break;
    case 258:
        payload->final_task = PollAndReleaseDefinitionChild(payload->final_task);
        if (payload->final_task == 0)
            context->state = 2;
        break;
    }
    return 0;
}

asm(".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer,0x080DD47D\n"
    ".global CopyCountedPaletteGroupsToShadow\n.thumb_set CopyCountedPaletteGroupsToShadow,0x080D45D1\n"
    ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080E03F9\n"
    ".global CleanupDefinitionEffectInputs\n.thumb_set CleanupDefinitionEffectInputs,0x080D38B5\n"
    ".global PollAndReleaseEffectStageTask\n.thumb_set PollAndReleaseEffectStageTask,0x080E05DD\n"
    ".global CreateManagedTaskChild\n.thumb_set CreateManagedTaskChild,0x080D7A71\n"
    ".global PollAndReleaseEffectFollowup\n.thumb_set PollAndReleaseEffectFollowup,0x080D7ABD\n"
    ".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005B6D\n"
    ".global PollAndReleaseDefinitionChild\n.thumb_set PollAndReleaseDefinitionChild,0x080E051D\n"
    ".global gInitialDefinitionsDefault\n.set gInitialDefinitionsDefault,0x08395720\n"
    ".global gInitialDefinitionsFour\n.set gInitialDefinitionsFour,0x08395738\n"
    ".global gInitialDefinitionsSix\n.set gInitialDefinitionsSix,0x08395750\n"
    ".global gInitialDefinitionsSeven\n.set gInitialDefinitionsSeven,0x0839575C\n"
    ".global gFollowupDefinitionsByType\n.set gFollowupDefinitionsByType,0x08395840\n"
    ".global gFollowupCountsByType\n.set gFollowupCountsByType,0x0839589C\n"
    ".global gDefinitionFinalCallbacks\n.set gDefinitionFinalCallbacks,0x08395C1C\n"
    ".global gDefinitionFinalPayloadSizes\n.set gDefinitionFinalPayloadSizes,0x08395C3C\n"
    ".global gCommonEffectPalette\n.set gCommonEffectPalette,0x088EA6D0\n"
    ".global gParameterEffectPaletteSix\n.set gParameterEffectPaletteSix,0x088EA550\n"
    ".global gParameterEffectPaletteSeven\n.set gParameterEffectPaletteSeven,0x088EA6D8\n"
    ".global gEffectPaletteNine\n.set gEffectPaletteNine,0x088E9C70\n"
    ".global gEffectPaletteTwelve\n.set gEffectPaletteTwelve,0x088E9C60\n"
    ".global gExtraEffectPaletteThirteen\n.set gExtraEffectPaletteThirteen,0x088EB260\n"
    ".global gEffectPaletteTwentyOne\n.set gEffectPaletteTwentyOne,0x088EA7F0\n"
    ".global gDefaultFollowupPalette\n.set gDefaultFollowupPalette,0x088EA66C\n"
    ".global gFollowupPaletteTwentyOne\n.set gFollowupPaletteTwentyOne,0x088EAFB0\n"
    ".global gFollowupPaletteTwentyTwo\n.set gFollowupPaletteTwentyTwo,0x088EB650\n");
