typedef unsigned int u32;
struct ListNode { void *value; struct ListNode *previous; struct ListNode *next; };
struct ListContainer { void *pool; struct ListNode *head; void *tree; };
typedef char NodeSize12[sizeof(struct ListNode) == 12 ? 1 : -1];
typedef char PreviousAt4[(u32)&((struct ListNode *)0)->previous == 4 ? 1 : -1];
typedef char NextAt8[(u32)&((struct ListNode *)0)->next == 8 ? 1 : -1];
extern void *AllocateListNode(void *pool, u32 size);
__asm__(".global AllocateListNode\n.thumb_set AllocateListNode,0x08007139");
/* The original requires successful allocation and an acyclic existing list. */
struct ListNode *AppendListNode(struct ListContainer *list, void *value)
{
    struct ListNode *node = AllocateListNode(list->pool, 12);
    struct ListNode *tail;
    node->value = value;
    node->next = 0;
    node->previous = 0;
    if (list->head == 0) {
        list->head = node;
    } else {
        tail = list->head;
        while (tail->next != 0)
            tail = tail->next;
        tail->next = node;
        node->previous = tail;
        node->next = 0;
    }
    return node;
}
