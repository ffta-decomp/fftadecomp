typedef unsigned int u32;
struct ListNode { u32 word; struct ListNode *previous, *next; };
struct TreeNode { u32 word0, word4; struct TreeNode *parent, *left, *right; };
struct TreeContainer { void *pool; struct ListNode *head; struct TreeNode *root; };
typedef char HeadAt4[(u32)&((struct TreeContainer *)0)->head == 4 ? 1 : -1];
typedef char RootAt8[(u32)&((struct TreeContainer *)0)->root == 8 ? 1 : -1];
extern void FreeRemainingListNodes(void *pool, struct ListNode *node);
extern void ReleaseContainerAllocation(void *pool, void *allocation);
__asm__(".global FreeRemainingListNodes\n.thumb_set FreeRemainingListNodes,0x080c7dc9\n.global ReleaseContainerAllocation\n.thumb_set ReleaseContainerAllocation,0x08007171");
static inline void ClearContainerListInline(struct TreeContainer *owner)
{
    struct TreeContainer *clear_owner = owner;
    register void *pool __asm__("r6");
    struct ListNode *head;
    /* Keep the defined clear alias separate, using an ordinary pseudo.
     * Hard r7 memory addresses undergo frame elimination in this compiler. */
    __asm__("" : "+r" (clear_owner));
    pool = owner->pool;
    /* Original retains this defined entry-pool snapshot in r6 across calls. */
    __asm__("" : "+r" (pool));
    head = owner->head;
    if (head != 0) {
        struct ListNode *next = head->next;
        if (next != 0)
            FreeRemainingListNodes(pool, next);
        ReleaseContainerAllocation(pool, head);
    }
    clear_owner->head = 0;
}
static inline void FreeTreeNodesInline(struct TreeContainer *container)
{
    register struct TreeContainer *clear_owner __asm__("r8") = container;
    void *pool;
    struct TreeNode *node;
    struct TreeNode *previous;
    struct TreeNode *root;
    /* The original retains this separate root-clear alias across traversal. */
    __asm__("" : "+r" (clear_owner));
    pool = container->pool;
    node = container->root;
    previous = (struct TreeNode *)-1;
    root = node;
scan_node:
    if (node != 0) {
        struct TreeNode *left = node->left;
        struct TreeNode *right = node->right;
        if (left != 0 && left != previous && right != previous) {
            previous = node;
            node = left;
            goto scan_node;
        }
        if (right != 0 && right != previous) {
            previous = node;
            node = right;
            goto scan_node;
        }
        ReleaseContainerAllocation(pool, node);
        if (node != root) {
            previous = node;
            node = node->parent;
            goto scan_node;
        }
    }
    {
        register struct TreeNode *cleared __asm__("r0") = 0;
        /* Preserve the original defined zero value before root-address materialization. */
        __asm__("" : "+r" (cleared));
        clear_owner->root = cleared;
    }
}
/* Each cleanup captures its own pool. The final pool is reloaded only after
 * both phases, retained across container release, and returned in full. */
void *DestroyTreeContainer(struct TreeContainer *container)
{
    register struct TreeContainer *final_owner __asm__("r9") = container;
    void *pool;
    /* Defined incoming alias retained for the original final pool reload. */
    __asm__("" : "+r" (final_owner));
    ClearContainerListInline(container);
    FreeTreeNodesInline(container);
    pool = final_owner->pool;
    ReleaseContainerAllocation(pool, container);
    return pool;
}
