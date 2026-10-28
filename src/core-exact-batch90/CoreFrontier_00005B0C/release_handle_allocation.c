struct AllocationHandle { void *storage; };
extern void FreeAllocation(void *storage, void *allocation);
asm(".global FreeAllocation\n.thumb_set FreeAllocation,0x08007171");
void ReleaseHandleAllocation(struct AllocationHandle *handle, void *allocation)
{
    FreeAllocation(handle->storage, allocation);
}
