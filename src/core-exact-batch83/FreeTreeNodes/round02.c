typedef unsigned int u32;
struct TreeNode { void *value; u32 key; struct TreeNode *parent, *left, *right; };
struct TreeContainer { void *pool; void *list; struct TreeNode *root; };
typedef char ParentAt8[(u32)&((struct TreeNode *)0)->parent == 8 ? 1 : -1];
typedef char LeftAt12[(u32)&((struct TreeNode *)0)->left == 12 ? 1 : -1];
typedef char RightAt16[(u32)&((struct TreeNode *)0)->right == 16 ? 1 : -1];
extern void ReleaseTreeAllocation(void *pool, void *node);
__asm__(".global ReleaseTreeAllocation\n.thumb_set ReleaseTreeAllocation,0x08007171");
/* The private allocator preserves the payload parent link after release.
 * Keep that parent read after the call, as in the original traversal. */
void FreeTreeNodes(struct TreeContainer *container)
{
    void *pool = container->pool;
    struct TreeNode *node = container->root;
    struct TreeNode *previous = (struct TreeNode *)-1;
    struct TreeNode *root = node;
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
        ReleaseTreeAllocation(pool, node);
        if (node != root) {
            previous = node;
            node = node->parent;
            goto scan_node;
        }
    }
    container->root = 0;
}
