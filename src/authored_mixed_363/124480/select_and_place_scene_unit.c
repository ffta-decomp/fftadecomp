#include "interfaces.h"
void SelectAndPlaceSceneUnit(u8 selector,u8 x,u8 y,u8 direction,u8 clear_activation)
    __asm__("ProcessSceneActionRecordSelection");
void SelectAndPlaceSceneUnit(u8 selector,u8 x,u8 y,u8 direction,u8 clear_activation)
{
    struct SceneGameUnit *unit;
    struct SceneGameEntity *entity;
    if (selector == 255) {
        register struct SceneGameUnit *cursor __asm__("r2") = gSceneSelectionUnits;
        int index;
        for (index = 0; index < 24;) {
            if (cursor->selection_flags & 0x400) {
                unit = cursor;
                goto selected;
            }
            ++index;
            __asm__ volatile("" : "+r"(index));
            {
                register u32 stride __asm__("r0")=264;
                __asm__ volatile("" : "+r"(stride));
                /* Real cursor advance: the initialized R2 pointer is
                   consumed by the next C field read or selected-unit copy. */
                __asm__("add %0, %0, %1"
                    : "+l"(cursor) : "l"(stride) : "cc");
            }
        }
        unit = 0;
    } else if ((s8)selector < 0) {
        unit = (struct SceneGameUnit *)ResolveEncodedSceneUnit(selector);
    } else {
        unit = FindSceneUnitById(selector);
    }
selected:
    unit->position_x = x;
    unit->position_y = y;
    unit->direction = direction;
    entity = ResolveSceneEntity(GetSceneSelectionContext(),unit);
    SetSelectedScenePosition(entity,(s8)entity->unit->position_x,
        (s8)entity->unit->position_y);
    entity->unit->backup_x = entity->unit->position_x;
    entity->unit->backup_y = entity->unit->position_y;
    ApplySelectedSceneAction(entity,1,direction);
    if (clear_activation)
        entity->flags &= ~1u;
    else
        entity->flags |= 1u;
}
