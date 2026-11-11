typedef unsigned int u32;
struct AllocationHandle { void *storage; };
extern void *AllocateMemory(void *storage,u32 byte_count);
asm(".global AllocateMemory\n.thumb_set AllocateMemory,0x08007139");
void *AllocateHandleMemory(struct AllocationHandle *handle,u32 byte_count)
{
    return AllocateMemory(handle->storage,byte_count);
}
