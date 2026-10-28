typedef unsigned int u32;
struct TaskNode;
struct TaskGroup;
extern u32 IsTaskStateTwo(const struct TaskNode *node);
extern void RemoveTaskSubtree(struct TaskGroup *group, struct TaskNode *node);
__asm__(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo, 0x08005bb1\n"
        ".global RemoveTaskSubtree\n.thumb_set RemoveTaskSubtree, 0x080058a5");

u32 PollAndReleaseManagedTask(void)
    __asm__("SceneActionDependency_000D37C4");
u32 PollAndReleaseManagedTask(void)
{
    struct TaskNode **slot = (struct TaskNode **)0x020159c0;
    if (*slot != 0) {
        if (IsTaskStateTwo(*slot) != 0) {
            /* Reload the slot after the query; removal keeps real callbacks. */
            RemoveTaskSubtree(*(struct TaskGroup **)0x0200f430, *slot);
            *slot = 0;
        }
        /* Completion is reported only on a subsequent empty-slot entry. */
        return 0;
    }
    return 1;
}
