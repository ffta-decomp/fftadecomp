#include "../task_tree_core.h"
extern void RemoveCurrentGroupTask(TaskNode *node);
void ReleaseOwnedEffectTask(TaskNode *node) __asm__("CoreDependency29_000D3EFC");
void ReleaseOwnedEffectTask(TaskNode *node)
{
    RemoveCurrentGroupTask(node);
}
__asm__(".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x08005b59");
