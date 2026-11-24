struct ListNode { unsigned int word; struct ListNode *previous; struct ListNode *next; };
struct ListOwner { void *pool; struct ListNode *head; };
extern void FreeRemainingListNodes(void *pool, struct ListNode *node);
extern void ReleaseHeadAllocation(void *pool, void *allocation);
void ClearContainerList(struct ListOwner *owner)
{
    void *pool = owner->pool;
    struct ListNode *head = owner->head;
    if (head != 0) {
        struct ListNode *next = head->next;
        if (next != 0)
            FreeRemainingListNodes(pool, next);
        ReleaseHeadAllocation(pool, head);
    }
    owner->head = 0;
}
asm(".global FreeRemainingListNodes\n.thumb_set FreeRemainingListNodes,0x080c7dc9\n.global ReleaseHeadAllocation\n.thumb_set ReleaseHeadAllocation,0x08007171\n");
