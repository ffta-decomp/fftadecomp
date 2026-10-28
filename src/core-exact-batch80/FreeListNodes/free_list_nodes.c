struct ListNode { unsigned int word; struct ListNode *previous; struct ListNode *next; };
extern void ReleaseListAllocation(void *pool, void *allocation);
void FreeListNodes(void *pool, struct ListNode *node)
{
    if (node != 0) {
        struct ListNode *next = node->next;
        if (next != 0)
            FreeListNodes(pool, next);
        ReleaseListAllocation(pool, node);
    }
}
asm(".global ReleaseListAllocation\n.thumb_set ReleaseListAllocation,0x08007171\n");
