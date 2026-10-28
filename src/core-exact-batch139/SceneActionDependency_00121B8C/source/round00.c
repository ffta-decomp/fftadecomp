#include "../../../../src/task_tree_core.h"
struct SceneTaskOwnerView { TaskGroup *group; };
extern struct SceneTaskOwnerView *gSceneOwner;
TaskNode *CreateSceneCommandTask(TaskCallback callback, u16 payload_bytes,
                                const u32 *event_template, TaskNode *parent)
{
    return CreateTaskNode_08005954(gSceneOwner->group, callback,
                                  payload_bytes, event_template, parent);
}
asm(".global gSceneOwner\n.set gSceneOwner,0x020159cc\n"
    ".global CreateTaskNode_08005954\n.thumb_set CreateTaskNode_08005954,0x08005955\n");
