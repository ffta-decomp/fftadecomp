#include "interfaces.h"

void RefreshSceneUnitPlacement_08124CE8(void)
{
    ScenePlacementUnit *unit = gUnitPoolA;
    int selected_ordinal = 0;
    int remaining = 11;

    do {
        if (unit->presence_code != 0) {
            ScenePlacementEntity *entity;
            entity = ResolvePlacementEntity(GetSceneActionContextBase(), unit);
            /* Preserve the unit-pointer reload between alias-visible byte stores. */
            entity->unit->saved_placement_x = entity->unit->placement_x;
            entity->unit->saved_placement_y = entity->unit->placement_y;
            ApplyPlacementState(entity, 1, unit->facing);
            if ((u8)UnitField27HasBit15(unit) != 0) {
                ScriptActorBinding *binding;
                u8 selector = selected_ordinal - 128;
                selected_ordinal++;
                binding = ResolveScriptActorBinding(selector);
                binding->unit = unit;
            }
        }
        remaining--;
        unit++;
    } while (remaining >= 0);
}
