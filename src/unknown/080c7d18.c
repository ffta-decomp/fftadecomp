typedef unsigned int u32;
struct TreeNode { u32 word0, word4; struct TreeNode *parent, *left, *right; };
struct TreeContainer { void *pool; void *list; struct TreeNode *root; };
typedef u32 (*TreeVisitor)(struct TreeNode *node, void *data);
typedef char ParentAt8[(u32)&((struct TreeNode *)0)->parent == 8 ? 1 : -1];
typedef char LeftAt12[(u32)&((struct TreeNode *)0)->left == 12 ? 1 : -1];
typedef char RightAt16[(u32)&((struct TreeNode *)0)->right == 16 ? 1 : -1];
/* This is the existing BX-r7 interworking entry, not an instruction body. */
__asm__(".global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
void TraverseTreeInOrder(struct TreeContainer *container, TreeVisitor callback, void *data)
{
    struct TreeNode *node = container->root;
    struct TreeNode *previous = (struct TreeNode *)-1;
    struct TreeNode *root = node;
    struct TreeNode *left;
    struct TreeNode *right;
scan_node:
    if (node != 0) {
        left = node->left;
        if (left != 0 && left != previous) {
            if (node->right == previous)
                goto ascend;
            previous = node;
            node = left;
            goto scan_node;
        }
        if (node->right == previous)
            goto ascend;
        if (callback(node, data) == 0)
            goto finished;
        right = node->right;
        if (right != 0) {
            previous = node;
            node = right;
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
