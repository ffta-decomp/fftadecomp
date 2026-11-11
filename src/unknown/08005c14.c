typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct TaskGroupStorageView {
    void *allocator;
    struct TaskNode *first_root;
    struct TaskNode *current;
    u16 phase;
};
extern void *InitializeTaskPool(void *storage, u32 byte_count);
extern void *AllocateTaskPoolBytes(void *pool, u32 byte_count);
__asm__(".global InitializeTaskPool\n.thumb_set InitializeTaskPool,0x080070c9\n.global AllocateTaskPoolBytes\n.thumb_set AllocateTaskPoolBytes,0x08007139");
struct TaskGroupStorageView *CreateTaskGroupStorage(void *storage, u32 byte_count)
    __asm__("SceneActionDependency_00005C14");
struct TaskGroupStorageView *CreateTaskGroupStorage(void *storage, u32 byte_count)
{
    void *pool = InitializeTaskPool(storage, byte_count);
    struct TaskGroupStorageView *group = AllocateTaskPoolBytes(pool, 16);
    group->allocator = pool;
    group->first_root = 0;
    group->current = 0;
    /* The halfword store leaves the final two allocation bytes untouched. */
    group->phase = 0;
    return group;
}
