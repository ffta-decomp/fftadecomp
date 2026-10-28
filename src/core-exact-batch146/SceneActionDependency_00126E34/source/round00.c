#include "../../../../src/task_tree_core.h"
struct SceneOwner { u8 unaccessed_00[6]; u8 complete; };
struct SceneUnit { u8 unaccessed_00[246]; u8 x; u8 y; u8 direction; };
struct DirectionEvent { u32 unassigned_phase; struct SceneOwner *owner; u32 unassigned_08; u32 unassigned_12; u32 unassigned_16; u16 unit_selector; u16 target; u16 unassigned_24; u16 unassigned_26; };
typedef char EventExtent[sizeof(struct DirectionEvent)==28?1:-1];
typedef char TargetOffset[(u32)&(((struct DirectionEvent *)0)->target)==22?1:-1];
typedef char UnitXOffset[(u32)&(((struct SceneUnit *)0)->x)==246?1:-1];
extern struct SceneUnit *ResolveSceneUnit(u8);
extern u32 DetermineSceneFacing(u8,u8,u8,u8);
extern u32 ProcessSceneActorDirectionTransition(TaskNode *,u16 *,void *);
extern TaskNode *CreateSceneCommandTask(TaskCallback,u16,const u32 *,TaskNode *);
void CreateSceneActorFacingRequest(struct SceneOwner *owner,u8 source_selector,u8 target_selector)
{
    struct DirectionEvent event;
    struct SceneUnit *source,*target;
    u8 facing;
    owner->complete=0;
    event.owner=owner;
    event.unit_selector=source_selector;
    source=ResolveSceneUnit(source_selector);
    target=ResolveSceneUnit(target_selector);
    facing=DetermineSceneFacing(source->x,source->y,target->x,target->y);
    if(facing==255)event.target=source->direction;
    else event.target=facing;
    /* No values are invented for the other transport bytes. */
    CreateSceneCommandTask((TaskCallback)ProcessSceneActorDirectionTransition,12,(const u32 *)&event,0);
}
asm(".global ResolveSceneUnit\n.thumb_set ResolveSceneUnit,0x08125579\n"
    ".global DetermineSceneFacing\n.thumb_set DetermineSceneFacing,0x08124acd\n"
    ".global ProcessSceneActorDirectionTransition\n.thumb_set ProcessSceneActorDirectionTransition,0x08126bfd\n"
    ".global CreateSceneCommandTask\n.thumb_set CreateSceneCommandTask,0x08121b8d\n");
