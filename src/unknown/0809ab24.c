typedef unsigned int u32;
struct RegistryReleaseContext { void *pool; };
extern u32 ReadNodeWord(const void *);
extern void ReleasePoolAllocation(void *, void *);
__asm__(".global ReadNodeWord\n.thumb_set ReadNodeWord, 0x080c7b75\n"
        ".global ReleasePoolAllocation\n.thumb_set ReleasePoolAllocation, 0x08007171");
u32 ReleaseRegistryNodePayload(const void *node, struct RegistryReleaseContext *context)
    __asm__("CoreRegion30_0009AB24");
u32 ReleaseRegistryNodePayload(const void *node, struct RegistryReleaseContext *context)
{
    void *allocation = (void *)ReadNodeWord(node);
    ReleasePoolAllocation(context->pool, allocation);
    return 1;
}
