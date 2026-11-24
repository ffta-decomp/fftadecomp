typedef unsigned int u32;
struct OwnedContainerPayload { u32 unknown_00; void *container; };
extern u32 ReadNodeWord(const void *);
extern void *DestroyTreeContainer(void *);
__asm__(".global ReadNodeWord\n.thumb_set ReadNodeWord, 0x080c7b75\n"
        ".global DestroyTreeContainer\n.thumb_set DestroyTreeContainer, 0x080c7909");
u32 ReleaseNodeOwnedContainer(const void *node, void *unused_context)
    __asm__("IsolatedCore57_000220B4");
u32 ReleaseNodeOwnedContainer(const void *node, void *unused_context)
{
    struct OwnedContainerPayload *payload = (struct OwnedContainerPayload *)ReadNodeWord(node);
    if (payload != (struct OwnedContainerPayload *)0)
        DestroyTreeContainer(payload->container);
    return 1;
}
