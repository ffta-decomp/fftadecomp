struct TaskGroupPoolView { void *pool; };
extern void ReleasePoolAllocation(void *pool, void *allocation);
extern void ClearFirstWord(void *address);
__asm__(".global ReleasePoolAllocation\n.thumb_set ReleasePoolAllocation,0x08007171\n.global ClearFirstWord\n.thumb_set ClearFirstWord,0x0800718d");
void ReleaseTaskGroupStorage(struct TaskGroupPoolView *group)
    __asm__("SceneActionDependency_00005C34");
void ReleaseTaskGroupStorage(struct TaskGroupPoolView *group)
{
    void *pool = group->pool;
    ReleasePoolAllocation(pool, group);
    /* The original clears the retained allocator, after freeing the group. */
    ClearFirstWord(pool);
}
