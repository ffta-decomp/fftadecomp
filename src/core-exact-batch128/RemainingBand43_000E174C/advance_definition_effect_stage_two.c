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
struct DefinitionStageTwo {
    u16 delay;
    u8 subtype;
    u8 unknown_03;
    u16 definition_id;
    u8 type;
    u8 completion_ready;
    u16 vertical_offset;
    s16 screen_x;
    s16 screen_y;
    u16 unknown_0e;
    void *record;
    void *resource;
    u8 effect_state[4];
    TaskNode *effect_task;
    TaskNode *main_motion;
    TaskNode *setup_motion;
    TaskNode *stage_task;
    u32 unknown_2c;
    void *source_record;
};
typedef char StageEventSize[sizeof(struct DefinitionStageEvent)==28?1:-1];
typedef char StagePayloadSize[sizeof(struct DefinitionStageTwo)==52?1:-1];
extern void ProjectDefinitionRecordPosition(const void *,s16 *,s16 *);
extern u8 ReadDefinitionRecordDirection(const void *);
extern TaskNode *CreateDefinitionSetupMotion(void *,u32,u32,u32,u32,TaskNode *);
extern TaskNode *PollAndReleaseDefinitionMotion(TaskNode *);
extern u32 ReadDefinitionRecordFlag20(const void *);
extern void *CreateDefinitionResourceById(u32,u32,int,int,u32,void *,u32,TaskNode *);
extern void *CreateDefinitionRawResource(const void *,u32,int,int,u32,u32,u32,u32);
extern void SetDefinitionResourceHidden(void *,u32);
extern void SetDefinitionResourceFlag8(void *,u32);
extern void DestroyDefinitionResource(void *);
extern void ApplyDefinitionRecordCurrentValue(void *,u16);
extern TaskNode *CreateDefinitionRecordMotion(void *,u8 *,u32,int,u32,u32,u32,TaskNode *);
extern TaskNode *CreateProjectedDefinitionEffect(int,int,u32,u32,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollAndReleaseProjectedEffect(TaskNode *);
extern void CopyOrFillHalfwords(const void *,void *,u32);
extern void CopyOrFillFastWords(const void *,void *,u32);
extern const u8 gDefinitionEffectCounts[];
extern const void *const gDefinitionEffectObjects[];
extern const u8 gDefinitionStageSequences[];
extern const u8 gFollowingStageSequence[];
extern const u8 gRawDefinitionDescriptor[];
extern u8 gDefinitionResourceTiles[];
extern u8 gDefinitionShadows[];
extern u8 gDefinitionTileTail[];
u32 AdvanceDefinitionEffectStageTwo(TaskNode *,struct DefinitionStageEvent *,struct DefinitionStageTwo *)
    asm("RemainingBand43_000E174C");
u32 AdvanceDefinitionEffectStageTwo(TaskNode *task,struct DefinitionStageEvent *event,
                                    struct DefinitionStageTwo *payload)
{
    switch (event->state) {
    case 0:
        payload->type=event->type;
        if (payload->type==12)
            payload->definition_id=362+event->subtype;
        else if (payload->type==14)
            payload->definition_id=event->subtype+201;
        else if (payload->type==15)
            payload->definition_id=event->subtype+229;
        payload->subtype=event->subtype;
        payload->record=event->record;
        payload->source_record=event->source_record;
        break;
    case 1:
        break;
    case 256:
        ProjectDefinitionRecordPosition(payload->record,&payload->screen_x,&payload->screen_y);
        if (payload->type==13) {
            int direction=(signed char)ReadDefinitionRecordDirection(payload->record);
            u32 axis=1;
            if (direction<=1)
                axis=0;
            payload->setup_motion=CreateDefinitionSetupMotion(payload->record,5,axis,4,0,task);
        }
        event->state++;
        break;
    case 257: {
        TaskNode *pending=PollAndReleaseDefinitionMotion(payload->setup_motion);
        u32 motion_mode;
        payload->setup_motion=pending;
        if (pending!=0)
            break;
        payload->vertical_offset=32;
        if ((u8)ReadDefinitionRecordFlag20(payload->record)!=0)
            payload->vertical_offset=16;
        motion_mode=1;
        switch (payload->type) {
        case 12:
        case 14:
        case 15:
            payload->resource=CreateDefinitionResourceById(payload->definition_id,0,
                payload->screen_x,(s16)((u16)payload->screen_y-payload->vertical_offset),
                0,gDefinitionResourceTiles,7,task);
            if (payload->type==15)
                motion_mode=3;
            break;
        case 13:
            payload->resource=CreateDefinitionRawResource(gRawDefinitionDescriptor,
                payload->subtype,payload->screen_x,
                (s16)((u16)payload->screen_y-payload->vertical_offset),
                984,7,(u32)pending,(u32)pending);
            break;
        }
        SetDefinitionResourceHidden(payload->resource,0);
        ApplyDefinitionRecordCurrentValue(payload->record,60);
        payload->main_motion=CreateDefinitionRecordMotion(payload->record,
            &payload->completion_ready,motion_mode,-1,0,53,0,task);
        event->state++;
        break;
    }
    case 258:
        if (payload->completion_ready==0)
            break;
        SetDefinitionResourceHidden(payload->resource,1);
        payload->stage_task=CreateDefinitionStageTask(gFollowingStageSequence,1,4,0,task);
        payload->delay=30;
        event->state++;
        break;
    case 259:
        payload->delay--;
        if (payload->delay!=0)
            break;
        payload->effect_task=CreateProjectedDefinitionEffect(payload->screen_x,
            (s16)((u16)payload->screen_y+32-payload->vertical_offset),0,0,
            gDefinitionEffectCounts[payload->type],payload->effect_state,
            gDefinitionEffectObjects[payload->type],task);
        payload->stage_task=CreateDefinitionStageTask(
            gDefinitionStageSequences+8*payload->type,1,4,0,task);
        SetDefinitionResourceFlag8(payload->resource,1);
        payload->delay=6;
        event->state++;
        break;
    case 260:
        if (payload->delay!=0) {
            u16 remaining=--payload->delay;
            if (remaining==0) {
                DestroyDefinitionResource(payload->resource);
                payload->resource=(void *)(u32)remaining;
            }
        }
        payload->effect_task=PollAndReleaseProjectedEffect(payload->effect_task);
        if (payload->effect_task==0)
            event->state++;
        break;
    case 261: {
        TaskNode *pending=PollAndReleaseDefinitionMotion(payload->main_motion);
        payload->main_motion=pending;
        if (pending==0) {
            u16 palette_zero;
            u16 object_zero;
            u32 tile_zero;
            register u8 *shadow asm("r4");
            register u8 *destination asm("r1");
            palette_zero=(u32)pending;
            shadow=gDefinitionShadows;
            destination=shadow;
            asm("" : : "r"(destination));
            CopyOrFillHalfwords(&palette_zero,destination,0x01000040);
            object_zero=(u32)pending;
            asm("" : : "r"(shadow));
            shadow+=512;
            asm("" : : "r"(shadow));
            destination=shadow;
            asm("" : : "r"(destination));
            CopyOrFillHalfwords(&object_zero,destination,0x01000070);
            tile_zero=(u32)pending;
            CopyOrFillFastWords(&tile_zero,gDefinitionTileTail,0x01000010);
            event->state=2;
        }
        break;
    }
    }
    return 0;
}
asm(".global ProjectDefinitionRecordPosition\n.thumb_set ProjectDefinitionRecordPosition,0x080dbdc9\n.global ReadDefinitionRecordDirection\n.thumb_set ReadDefinitionRecordDirection,0x080dbc89\n.global CreateDefinitionSetupMotion\n.thumb_set CreateDefinitionSetupMotion,0x080df7a1\n.global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x080dba5d\n.global ReadDefinitionRecordFlag20\n.thumb_set ReadDefinitionRecordFlag20,0x080df8b1\n.global CreateDefinitionResourceById\n.thumb_set CreateDefinitionResourceById,0x080d5fd9\n.global CreateDefinitionRawResource\n.thumb_set CreateDefinitionRawResource,0x080d5cc1\n.global SetDefinitionResourceHidden\n.thumb_set SetDefinitionResourceHidden,0x0801115d\n.global SetDefinitionResourceFlag8\n.thumb_set SetDefinitionResourceFlag8,0x080111a9\n.global DestroyDefinitionResource\n.thumb_set DestroyDefinitionResource,0x08011429\n.global ApplyDefinitionRecordCurrentValue\n.thumb_set ApplyDefinitionRecordCurrentValue,0x080de10d\n.global CreateDefinitionRecordMotion\n.thumb_set CreateDefinitionRecordMotion,0x080de4b1\n.global CreateProjectedDefinitionEffect\n.thumb_set CreateProjectedDefinitionEffect,0x080d6099\n.global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080dfd8d\n.global PollAndReleaseProjectedEffect\n.thumb_set PollAndReleaseProjectedEffect,0x080d6135\n.global CopyOrFillHalfwords\n.thumb_set CopyOrFillHalfwords,0x0814186d\n.global CopyOrFillFastWords\n.thumb_set CopyOrFillFastWords,0x08141869\n.global gDefinitionEffectCounts\n.set gDefinitionEffectCounts,0x08395aa8\n.global gDefinitionEffectObjects\n.set gDefinitionEffectObjects,0x08395a4c\n.global gDefinitionStageSequences\n.set gDefinitionStageSequences,0x08395adc\n.global gFollowingStageSequence\n.set gFollowingStageSequence,0x08395b8c\n.global gRawDefinitionDescriptor\n.set gRawDefinitionDescriptor,0x08506b30\n.global gDefinitionResourceTiles\n.set gDefinitionResourceTiles,0x06017e00\n.global gDefinitionShadows\n.set gDefinitionShadows,0x03003920\n.global gDefinitionTileTail\n.set gDefinitionTileTail,0x0600ffc0\n");
