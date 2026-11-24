typedef unsigned int u32;
struct BoundAllocationContext { void *pool; };
extern struct BoundAllocationContext *BoundAllocationContextCell;
extern void *AllocateBoundPool_08007138(void *, u32);
void *CoreDependency29_00005B28(u32 bytes)
{
    return AllocateBoundPool_08007138(BoundAllocationContextCell->pool, bytes);
}
asm(".set BoundAllocationContextCell,0x02008ff0\n.thumb_set AllocateBoundPool_08007138,0x08007139\n");
