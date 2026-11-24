typedef signed short s16;
typedef unsigned char u8;
struct TaskGroup;
struct ManagedResultContextView {
    s16 result;
    u8 ready;
    u8 unknown_03[29];
    struct TaskGroup *group;
    void *allocation;
};
extern struct ManagedResultContextView *gCurrentManagedResult;
extern void RunTaskTree(struct TaskGroup *group);
extern void RemoveFirstTaskRoot(struct TaskGroup *group);
extern void ReleaseTaskGroupStorage(struct TaskGroup *group);
extern void ReleaseGlobalPoolAllocation(void *allocation);
__asm__(".global gCurrentManagedResult\n.set gCurrentManagedResult,0x0200f438\n.global RunTaskTree\n.thumb_set RunTaskTree,0x08005a25\n.global RemoveFirstTaskRoot\n.thumb_set RemoveFirstTaskRoot,0x08005b19\n.global ReleaseTaskGroupStorage\n.thumb_set ReleaseTaskGroupStorage,0x08005c35\n.global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation,0x08022855");
void ReleaseCurrentManagedResultContext(void) __asm__("SceneRegisteredRoot_00025374");
void ReleaseCurrentManagedResultContext(void)
{
    if (gCurrentManagedResult != 0) {
        void *allocation = gCurrentManagedResult->allocation;
        /* Callback effects require the current record to be reloaded after each helper. */
        RunTaskTree(gCurrentManagedResult->group);
        RemoveFirstTaskRoot(gCurrentManagedResult->group);
        ReleaseTaskGroupStorage(gCurrentManagedResult->group);
        gCurrentManagedResult->group = 0;
        ReleaseGlobalPoolAllocation(allocation);
        gCurrentManagedResult = 0;
    }
}
