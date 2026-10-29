#include "interfaces.h"
void PlaceSceneUnitAtContentPosition(u8 encoded_id, u8 placement_slot) __asm__("SceneActionDependency_00124560");
void PlaceSceneUnitAtContentPosition(u8 encoded_id, u8 placement_slot)
{
    struct SceneUnit *unit;
    struct SceneActor *actor;
    if (encoded_id == 255) {
        struct SceneUnit *cursor = (struct SceneUnit *)0x02000080;
        s32 index = 0;
        register u32 selection_mask asm("r4") = 0x400;
        asm("" : "+r"(selection_mask));
        for (; index <= 23;) {
            register u32 observed_flags asm("r1") = cursor->flags;
            asm("" : "+r"(observed_flags));
            if (selection_mask & observed_flags) {
                unit = cursor;
                goto unit_selected;
            }
            ++index;
            {
            register u32 record_stride asm("r0") = sizeof(*cursor);
            asm("" : "+r"(record_stride));
            cursor = (struct SceneUnit *)((u8 *)cursor + record_stride);
            }
        }
        unit = 0;
    } else if ((signed char)encoded_id < 0) {
        unit = (struct SceneUnit *)ResolveSceneUnitByEncodedId(encoded_id);
    } else {
        unit = (struct SceneUnit *)FindUnitPoolRecordById(encoded_id);
    }
unit_selected:
    actor = FindExistingActor(GetContentConsumerContext(), unit);
    if (actor == 0) {
        const struct ContentPlacementRecord *content;
        const u8 *position;
        struct SceneActor *reference;
        s32 position_offset;
        content = &((const struct ContentPlacementRecord *)0x0854cd54)[ReadCurrentContentIndex()];
        position = content->positions;
        position_offset = placement_slot * 2 - 2;
        position += position_offset;
        reference = FindSceneUnitByStatusPriority();
        unit->x = position[0];
        unit->y = position[1];
        unit->facing = DetermineSceneFacing(unit->x, unit->y, reference->unit->x, reference->unit->y);
        actor = FindOrCreateBattleActor(GetContentConsumerContext(), unit);
        actor->unit->previous_x = actor->unit->x;
        actor->unit->previous_y = actor->unit->y;
        SetUnitStateEDBit7(actor->unit, 1);
    }
    ReapplySceneActorState(actor, 0, 0);
}
