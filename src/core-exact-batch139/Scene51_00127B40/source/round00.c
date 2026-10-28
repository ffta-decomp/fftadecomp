#include "../../../../src/task_tree_core.h"
struct SceneCommandOwner {
    u8 unaccessed_00[6];
    u8 complete;
    u8 unaccessed_07;
    TaskNode *parent;
};
struct SceneCoordinateEventTemplate {
    u32 unassigned_phase;
    struct SceneCommandOwner *owner;
    u32 tail;
    u32 unassigned_12;
    u32 unassigned_16;
    u16 unit_selector;
    u16 path_selector;
    u16 delay;
    u16 unassigned_26;
};
typedef char EventExtent[sizeof(struct SceneCoordinateEventTemplate)==28?1:-1];
typedef char SelectorOffset[(u32)&(((struct SceneCoordinateEventTemplate *)0)->unit_selector)==20?1:-1];
typedef char DelayOffset[(u32)&(((struct SceneCoordinateEventTemplate *)0)->delay)==24?1:-1];
extern u32 ProcessSceneCoordinateCommand(TaskNode *, u16 *, void *);
extern TaskNode *CreateSceneCommandTask(TaskCallback callback, u16 payload_bytes,
                                      const u32 *event_template, TaskNode *parent);
void CreateSceneCoordinateRequest(struct SceneCommandOwner *owner, u8 unit_selector,
                           u8 path_selector, u8 delay, u8 tail)
{
    struct SceneCoordinateEventTemplate event;
    owner->complete = 0;
    event.owner = owner;
    event.tail = tail;
    event.unit_selector = unit_selector;
    event.path_selector = path_selector;
    event.delay = delay;
    /* Leave unspecified transport bytes intact, as in the original frame. */
    CreateSceneCommandTask((TaskCallback)ProcessSceneCoordinateCommand, 16,
                           (const u32 *)&event, owner->parent);
}
asm(".global ProcessSceneCoordinateCommand\n.thumb_set ProcessSceneCoordinateCommand,0x08127125\n"
    ".global CreateSceneCommandTask\n.thumb_set CreateSceneCommandTask,0x08121b8d\n");
