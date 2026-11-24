typedef unsigned int u32;
struct ListNode;
extern u32 ReadNodeWord(const struct ListNode *);
extern void ReleaseNodePayload(void *, void *);
u32 ReleaseNodeAllocation(struct ListNode *node, void *pool)
{
    void *allocation = (void *)ReadNodeWord(node);
    if (allocation != 0)
        ReleaseNodePayload(pool, allocation);
    return 1;
}
asm(".global ReadNodeWord\n.thumb_set ReadNodeWord,0x080c7b75\n.global ReleaseNodePayload\n.thumb_set ReleaseNodePayload,0x08007171\n");
