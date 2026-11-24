struct ListNode { unsigned int word; struct ListNode *previous; struct ListNode *next; };
struct ListOwner { void *pool; struct ListNode *head; };
extern void ReleaseListNodeAllocation(void *pool, void *allocation);
void UnlinkAndFreeListNode(struct ListOwner *owner, struct ListNode *node)
{
    struct ListNode *previous = node->previous;
    if (previous == 0)
        owner->head = node->next;
    else
        previous->next = node->next;
    {
        struct ListNode *next = node->next;
        if (next != 0)
            next->previous = node->previous;
    }
    ReleaseListNodeAllocation(owner->pool, node);
}
asm(".global ReleaseListNodeAllocation\n.thumb_set ReleaseListNodeAllocation,0x08007171\n");
