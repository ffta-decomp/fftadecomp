struct TaskNode;
struct TaskGroupRootView { void *allocator; struct TaskNode *first_root; };
extern void RemoveTaskSubtree(struct TaskGroupRootView *group, struct TaskNode *root);
__asm__(".global RemoveTaskSubtree\n.thumb_set RemoveTaskSubtree,0x080058a5");
void RemoveFirstTaskRoot(struct TaskGroupRootView *group)
    __asm__("SceneActionDependency_00005B18");
void RemoveFirstTaskRoot(struct TaskGroupRootView *group)
{
    if (group->first_root != 0)
        RemoveTaskSubtree(group, group->first_root);
}
