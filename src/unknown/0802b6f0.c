struct TaskGroup;
struct UnitTaskGroupView { struct TaskGroup *group; };
extern struct UnitTaskGroupView *gCurrentUnitTasks;
extern void RunUnitTaskTree(struct TaskGroup *group);
__asm__(".global gCurrentUnitTasks\n.set gCurrentUnitTasks,0x0200f440\n.global RunUnitTaskTree\n.thumb_set RunUnitTaskTree,0x08005a25");
void RunCurrentUnitTasks(void) __asm__("SceneRegisteredRoot_0002B6F0");
void RunCurrentUnitTasks(void)
{
    if (gCurrentUnitTasks != 0 && gCurrentUnitTasks->group != 0)
        RunUnitTaskTree(gCurrentUnitTasks->group);
}
