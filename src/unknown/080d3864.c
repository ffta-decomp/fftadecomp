struct TaskGroup;
struct TaskNode;
extern void RemoveTaskSubtree(struct TaskGroup *, struct TaskNode *);
__asm__(".global RemoveTaskSubtree\n.thumb_set RemoveTaskSubtree, 0x080058a5");

/* The actual removal retains all real task callbacks, unlinking and frees. */
void RemoveManagedTask(struct TaskNode *node)
    __asm__("SceneActionDependency_000D3864");
void RemoveManagedTask(struct TaskNode *node)
{
    RemoveTaskSubtree(*(struct TaskGroup **)0x0200f430, node);
}
