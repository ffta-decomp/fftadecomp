typedef unsigned int u32;
struct Node { u32 word0, word4; struct Node *parent, *left, *right; };
struct Container { void *pool; void *list; struct Node *root; };
u32 CountContainerTreeNodes(struct Container *container)
{
    struct Node *entry_root = container->root;
    struct Node *node;
    struct Node *previous;
    struct Node *root;
    struct Node *right;
    struct Node *left;
    u32 count;
    u32 result;
    if (entry_root == 0) {
        result = 0;
        goto finished;
    }
    node = entry_root;
    count = 0;
    previous = (struct Node *)-1;
    root = node;
    goto scan_node;
ascend:
    previous = node;
    node = node->parent;
scan_node:
    if (node != 0) {
        right = node->right;
        if (right != 0 && right != previous) {
            if (node->left == previous)
                goto check_root;
            previous = node;
            node = right;
            goto scan_node;
        }
        left = node->left;
        if (left == previous)
            goto check_root;
        count++;
        if (left != 0) {
            previous = node;
            node = left;
            goto scan_node;
        }
check_root:
        if (node != root)
            goto ascend;
    }
    result = count;
finished:
    return result;
}
