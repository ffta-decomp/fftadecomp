typedef unsigned int u32;
struct TreeNode { u32 word0, word4; struct TreeNode *parent, *left, *right; };
struct TreeContainer { void *pool; void *list; struct TreeNode *root; };
typedef u32 (*TreeVisitor)(struct TreeNode *node, void *data);
typedef char ParentAt8[(u32)&((struct TreeNode *)0)->parent == 8 ? 1 : -1];
typedef char LeftAt12[(u32)&((struct TreeNode *)0)->left == 12 ? 1 : -1];
typedef char RightAt16[(u32)&((struct TreeNode *)0)->right == 16 ? 1 : -1];
/* This is the existing BX-r7 interworking entry, not an instruction body. */
__asm__(".global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
void TraverseTreeReverseInOrder(struct TreeContainer *container, TreeVisitor callback, void *data)
{
    struct TreeNode *node = container->root;
    struct TreeNode *previous = (struct TreeNode *)-1;
    struct TreeNode *root = node;
    struct TreeNode *right;
    struct TreeNode *left;
scan_node:
    if (node != 0) {
        right = node->right;
        if (right != 0 && right != previous) {
            if (node->left == previous)
                goto ascend;
            previous = node;
            node = right;
            goto scan_node;
        }
        if (node->left == previous)
            goto ascend;
        if (callback(node, data) == 0)
            goto finished;
        left = node->left;
        if (left != 0) {
            previous = node;
            node = left;
            goto scan_node;
        }
    ascend:
        if (node == root)
            goto finished;
        previous = node;
        node = node->parent;
        goto scan_node;
    }
finished:
    ;
}
