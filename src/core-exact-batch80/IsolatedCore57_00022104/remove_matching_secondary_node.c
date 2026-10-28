typedef unsigned int u32;
struct ListNode; struct ListOwner;
extern u32 ReadNodeWord(const struct ListNode *);
extern struct ListNode *FindMatchingNode(struct ListOwner *, u32);
extern void RemoveMatchingNode(struct ListOwner *, struct ListNode *);
u32 RemoveMatchingSecondaryNode(struct ListNode *node, struct ListOwner *owner)
{
    struct ListNode *match = FindMatchingNode(owner, ReadNodeWord(node));
    if (match != 0)
        RemoveMatchingNode(owner, match);
    return 1;
}
asm(".global ReadNodeWord\n.thumb_set ReadNodeWord,0x080c7b75\n.global FindMatchingNode\n.thumb_set FindMatchingNode,0x080c7bf5\n.global RemoveMatchingNode\n.thumb_set RemoveMatchingNode,0x080c7a35\n");
