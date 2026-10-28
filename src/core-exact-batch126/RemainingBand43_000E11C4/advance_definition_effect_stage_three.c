#include "../../../src/task_tree_core.h"

typedef signed short s16;
struct DefinitionStageEvent {
    u16 state;
    u16 unknown_02;
    void *record;
    void *source_record;
    u32 unknown_0c[2];
    u16 type;
    u16 subtype;
    u16 unknown_18[2];
};
struct DefinitionStageThree {
    u16 delay;
    u8 type;
    u8 completion_ready;
    s16 screen_x;
    s16 screen_y;
    void *record;
    u8 effect_state[16];
    TaskNode *effect_task;
    TaskNode *child_task;
    TaskNode *final_motion;
    TaskNode *initial_motion;
    TaskNode *initial_stage;
    TaskNode *following_stage;
    void *source_record;
};
typedef char StageEventSize[sizeof(struct DefinitionStageEvent)==28?1:-1];
typedef char StagePayloadSize[sizeof(struct DefinitionStageThree)==56?1:-1];
extern void ApplyDefinitionRecordCurrentValue(void *,u16);
extern TaskNode *CreateDefinitionRecordMotion(void *,u8 *,u32,int,u32,u32,u32,TaskNode *);
extern void ProjectDefinitionRecordPosition(const void *,s16 *,s16 *);
extern TaskNode *CreateProjectedDefinitionEffect(int,int,u32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionStageChild(TaskNode *,u16 *,void *);
extern void RestoreBattleRecordDirections(u8,void *,void *);
extern TaskNode *PollAndReleaseProjectedEffect(TaskNode *);
extern TaskNode *PollAndReleaseDefinitionMotion(TaskNode *);
extern TaskNode *PollAndReleaseDefinitionChild(TaskNode *);
extern TaskNode *CreateDefinitionRecordTask(u8,u32,void *,u16,u16,TaskNode *);
extern void CopyOrFillHalfwords(const void *,void *,u32);
extern void CopyOrFillFastWords(const void *,void *,u32);
extern const u8 gDefinitionEffectCounts[];
extern const void *const gDefinitionEffectObjects[];
extern const u8 gDefinitionStageSequences[];
extern const u8 gFollowingStageSequence[];
extern u8 gDefinitionShadows[];
extern u8 gDefinitionTileTail[];
u32 AdvanceDefinitionEffectStageThree(TaskNode *task,
                                     struct DefinitionStageEvent *event,
                                     struct DefinitionStageThree *payload)
    asm("RemainingBand43_000E11C4");
u32 AdvanceDefinitionEffectStageThree(TaskNode *task,
                                     struct DefinitionStageEvent *event,
                                     struct DefinitionStageThree *payload)
{
    u32 child_event[7];
    switch (event->state) {
    case 0:
        payload->type=event->type;
        payload->record=event->record;
        payload->source_record=event->source_record;
        break;
    case 1:
        break;
    case 256:
        ApplyDefinitionRecordCurrentValue(payload->record,60);
        payload->initial_motion=CreateDefinitionRecordMotion(payload->record,
            &payload->completion_ready,1,-1,0,50,0,task);
        event->state++;
        break;
    case 257:
        if (payload->completion_ready==0)
            break;
        ProjectDefinitionRecordPosition(payload->record,
                                        &payload->screen_x,&payload->screen_y);
        payload->effect_task=CreateProjectedDefinitionEffect(payload->screen_x,
            payload->screen_y,0,0,gDefinitionEffectCounts[payload->type],
            payload->effect_state,gDefinitionEffectObjects[payload->type],task);
        payload->initial_stage=CreateDefinitionStageTask(
            gDefinitionStageSequences+8*payload->type,1,4,0,task);
        /* Only the child callback's consumed fields are initialized. */
        ((u16 *)child_event)[10]=payload->type;
        child_event[1]=(u32)payload->record;
        payload->child_task=CreateTaskInCurrentGroup(DefinitionStageChild,
                                                    44,child_event,task);
        RestoreBattleRecordDirections(6,0,payload->record);
        event->state++;
        break;
    case 258:
        payload->effect_task=PollAndReleaseProjectedEffect(payload->effect_task);
        if (payload->effect_task!=0)
            break;
        payload->initial_motion=PollAndReleaseDefinitionMotion(payload->initial_motion);
        if (payload->initial_motion!=0)
            break;
        payload->child_task=PollAndReleaseDefinitionChild(payload->child_task);
        if (payload->child_task!=0)
            break;
        payload->following_stage=CreateDefinitionStageTask(gFollowingStageSequence,
                                                          1,4,0,task);
        payload->delay=10;
        event->state++;
        break;
    case 259:
        payload->delay--;
        if (payload->delay!=0)
            break;
        payload->final_motion=CreateDefinitionRecordTask(5,0,payload->record,
                                                       16,0,task);
        event->state++;
        break;
    case 260: {
        TaskNode *pending=PollAndReleaseDefinitionMotion(payload->final_motion);
        payload->final_motion=pending;
        if (pending==0) {
            struct { u16 palette; u16 object; u32 tile; } zeros;
            u16 *palette_source = &zeros.palette;
            register u8 *shadow asm("r4");
            register u8 *destination asm("r1");
            register const void *fill_source asm("r0");
            /* The native source address exists before its first halfword write. */
            asm("" : : "r"(palette_source));
            *palette_source=(u32)pending;
            shadow=gDefinitionShadows;
            fill_source=palette_source;
            asm("" : : "r"(fill_source));
            destination=shadow;
            /* Preserve the original initialized fill base/argument lifetimes. */
            asm("" : : "r"(destination));
            CopyOrFillHalfwords(fill_source,destination,0x01000040);
            fill_source=&zeros.object;
            asm("" : : "r"(fill_source));
            *(u16 *)fill_source=(u32)pending;
            asm("" : : "r"(shadow));
            shadow+=512;
            asm("" : : "r"(shadow));
            destination=shadow;
            asm("" : : "r"(destination));
            CopyOrFillHalfwords(fill_source,destination,0x01000070);
            zeros.tile=(u32)pending;
            CopyOrFillFastWords(&zeros.tile,gDefinitionTileTail,0x01000010);
            event->state=2;
        }
        break;
    }
    }
    return 0;
}
asm(".global ApplyDefinitionRecordCurrentValue\n.thumb_set ApplyDefinitionRecordCurrentValue,0x080de10d\n"
    ".global CreateDefinitionRecordMotion\n.thumb_set CreateDefinitionRecordMotion,0x080de4b1\n"
    ".global ProjectDefinitionRecordPosition\n.thumb_set ProjectDefinitionRecordPosition,0x080dbdc9\n"
    ".global CreateProjectedDefinitionEffect\n.thumb_set CreateProjectedDefinitionEffect,0x080d6099\n"
    ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080dfd8d\n"
    ".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global DefinitionStageChild\n.thumb_set DefinitionStageChild,0x080e0cc5\n"
    ".global RestoreBattleRecordDirections\n.thumb_set RestoreBattleRecordDirections,0x080de2d1\n"
    ".global PollAndReleaseProjectedEffect\n.thumb_set PollAndReleaseProjectedEffect,0x080d6135\n"
    ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x080dba5d\n"
    ".global PollAndReleaseDefinitionChild\n.thumb_set PollAndReleaseDefinitionChild,0x080e051d\n"
    ".global CreateDefinitionRecordTask\n.thumb_set CreateDefinitionRecordTask,0x080df9ad\n"
    ".global CopyOrFillHalfwords\n.thumb_set CopyOrFillHalfwords,0x0814186d\n"
    ".global CopyOrFillFastWords\n.thumb_set CopyOrFillFastWords,0x08141869\n"
    ".global gDefinitionEffectCounts\n.set gDefinitionEffectCounts,0x08395aa8\n"
    ".global gDefinitionEffectObjects\n.set gDefinitionEffectObjects,0x08395a4c\n"
    ".global gDefinitionStageSequences\n.set gDefinitionStageSequences,0x08395adc\n"
    ".global gFollowingStageSequence\n.set gFollowingStageSequence,0x08395b7c\n"
    ".global gDefinitionShadows\n.set gDefinitionShadows,0x03003920\n"
    ".global gDefinitionTileTail\n.set gDefinitionTileTail,0x0600ffc0\n");
