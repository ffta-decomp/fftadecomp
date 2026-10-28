struct TaskGroup;
struct TaskNode;
struct UnitTaskContextView {
    struct TaskGroup *group;
    void *allocation;
    struct TaskNode *primary;
    struct TaskNode *secondary;
};
extern struct UnitTaskContextView *gCurrentUnitTasks;
extern void RunUnitTaskTree(struct TaskGroup *group);
extern void RemoveUnitTaskSubtree(struct TaskGroup *group, struct TaskNode *node);
extern void ReleaseUnitTaskGroup(struct TaskGroup *group);
extern void ReleaseGlobalPoolAllocation(void *allocation);
__asm__(".global gCurrentUnitTasks\n.set gCurrentUnitTasks,0x0200f440\n.global RunUnitTaskTree\n.thumb_set RunUnitTaskTree,0x08005a25\n.global RemoveUnitTaskSubtree\n.thumb_set RemoveUnitTaskSubtree,0x080058a5\n.global ReleaseUnitTaskGroup\n.thumb_set ReleaseUnitTaskGroup,0x08005c35\n.global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation,0x08022855");
void ReleaseCurrentUnitTaskContext(void) __asm__("SceneRegisteredRoot_0002B6A0");
void ReleaseCurrentUnitTaskContext(void)
{
    if (gCurrentUnitTasks != 0) {
        void *allocation = gCurrentUnitTasks->allocation;
        /* This is a final scheduler pass, so subsequent fields must be reloaded. */
        RunUnitTaskTree(gCurrentUnitTasks->group);
        if (gCurrentUnitTasks->primary != 0)
            RemoveUnitTaskSubtree(gCurrentUnitTasks->group, gCurrentUnitTasks->primary);
        if (gCurrentUnitTasks->secondary != 0)
            RemoveUnitTaskSubtree(gCurrentUnitTasks->group, gCurrentUnitTasks->secondary);
        ReleaseUnitTaskGroup(gCurrentUnitTasks->group);
        gCurrentUnitTasks->group = 0;
        ReleaseGlobalPoolAllocation(allocation);
        gCurrentUnitTasks = 0;
    }
}
