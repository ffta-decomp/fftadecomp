typedef unsigned int u32;
typedef signed int s32;
struct TreeNode { s32 key; void *payload; struct TreeNode *parent, *left, *right; u32 word20; };
struct Container { void *pool; void *list; struct TreeNode *root; };
typedef char NodeSize24[sizeof(struct TreeNode) == 24 ? 1 : -1];
extern void *AllocateTreeNode(void *pool, u32 bytes);
__asm__(".global AllocateTreeNode\n.thumb_set AllocateTreeNode,0x08007139");
struct TreeNode *InsertContainerTreeNode(struct Container *container, void *payload, s32 key)
{
    struct TreeNode *node = AllocateTreeNode(container->pool, 24);
    struct TreeNode *entry_root;
    struct TreeNode *parent;
    struct TreeNode *child;
    s32 search_key;
    node->payload = payload;
    node->key = key;
    node->parent = 0;
    node->left = 0;
    node->right = 0;
    node->word20 = 0;
    entry_root = container->root;
    if (entry_root == 0) {
        container->root = node;
        goto finished;
    }
    parent = entry_root;
    search_key = key;
scan_parent:
    if (search_key < parent->key) {
        child = parent->left;
        if (child != 0)
            goto advance;
        parent->left = node;
        goto linked;
    }
    child = parent->right;
    if (child == 0)
        goto link_right;
advance:
    parent = child;
    goto scan_parent;
link_right:
    parent->right = node;
linked:
    node->parent = parent;
finished:
    return node;
}
