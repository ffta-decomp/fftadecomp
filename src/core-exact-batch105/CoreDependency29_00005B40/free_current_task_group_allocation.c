struct PoolAllocator;
struct CurrentTaskGroupView {
    struct PoolAllocator *allocator;
};
extern struct CurrentTaskGroupView * volatile gCurrentTaskGroup;
extern void FreePoolAllocation_08007170(struct PoolAllocator *, void *allocation);
__asm__(".global gCurrentTaskGroup\n.set gCurrentTaskGroup,0x02008ff0\n.global FreePoolAllocation_08007170\n.thumb_set FreePoolAllocation_08007170,0x08007171");
void FreeCurrentTaskGroupAllocation(void *allocation) __asm__("CoreDependency29_00005B40");
void FreeCurrentTaskGroupAllocation(void *allocation)
{
    FreePoolAllocation_08007170(gCurrentTaskGroup->allocator, allocation);
}
