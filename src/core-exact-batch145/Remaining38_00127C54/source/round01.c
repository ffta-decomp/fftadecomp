#include "../../../../src/task_tree_core.h"
typedef signed int s32;
struct SceneCommandOwner {
    u8 unaccessed_00[6];
    u8 complete;
    u8 unaccessed_07;
    TaskNode *parent;
};
struct SceneHeightEventTemplate {
    u32 unassigned_phase;
    struct SceneCommandOwner *owner;
    s32 height_delta;
    u32 unassigned_12;
    u32 unassigned_16;
    u16 unit_selector;
    u16 mode;
    u16 duration;
    u16 unassigned_26;
};
typedef char EventExtent[sizeof(struct SceneHeightEventTemplate)==28?1:-1];
typedef char SelectorOffset[(u32)&(((struct SceneHeightEventTemplate *)0)->unit_selector)==20?1:-1];
typedef char DurationOffset[(u32)&(((struct SceneHeightEventTemplate *)0)->duration)==24?1:-1];
extern u32 ProcessSceneActorHeightTransition(TaskNode *,u16 *,void *);
extern TaskNode *CreateSceneCommandTask(TaskCallback,u16,const u32 *,TaskNode *);
void CreateSceneActorHeightTransition(struct SceneCommandOwner *owner,
                                     s32 packed_height,u32 packed_duration)
{
    struct SceneHeightEventTemplate event;
    struct SceneHeightEventTemplate *fields;
    register u32 projection __asm__("r0");
    owner->complete=0;
    event.owner=owner;
    event.height_delta=packed_height>>16;
    fields=&event;
    /* Initialized destructive projections retain the native working register
       and the one real event base; these constraints emit no instructions. */
    projection=(u32)packed_height<<24;
    asm("" : "+r"(projection) : "r"(fields));
    projection>>=24;
    fields->unit_selector=projection;
    projection=(u32)packed_height>>8;
    asm("" : "+r"(projection));
    fields->mode=(u8)projection;
    projection=packed_duration>>16;
    asm("" : "+r"(projection));
    fields->duration=projection;
    /* Only the initialized transport fields belong to this producer. */
    CreateSceneCommandTask((TaskCallback)ProcessSceneActorHeightTransition,320,
                          (const u32 *)&event,owner->parent);
}
asm(".global ProcessSceneActorHeightTransition\n.thumb_set ProcessSceneActorHeightTransition,0x08127a1d\n"
    ".global CreateSceneCommandTask\n.thumb_set CreateSceneCommandTask,0x08121b8d\n");
