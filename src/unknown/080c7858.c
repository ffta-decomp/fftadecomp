typedef unsigned int u32;
typedef signed int s32;
struct TreeNode { s32 ordering_value; void *payload; struct TreeNode *parent, *left, *right; };
struct TreeContainer { void *pool; void *list; struct TreeNode *root; };
typedef char ParentAt8[(u32)&((struct TreeNode *)0)->parent == 8 ? 1 : -1];
typedef char LeftAt12[(u32)&((struct TreeNode *)0)->left == 12 ? 1 : -1];
typedef char RightAt16[(u32)&((struct TreeNode *)0)->right == 16 ? 1 : -1];
/* Detach without freeing. Each remaining subtree is reinserted independently;
 * equal signed ordering words take the right edge. */
void DetachTreeNode(struct TreeContainer *container, struct TreeNode *node)
{
    struct TreeNode *parent = node->parent;
    struct TreeNode *subtree;
    struct TreeNode *cursor;
    struct TreeNode *next;
    s32 ordering_value;
    if (parent == 0) {
        container->root = parent;
        if (node->left != 0) {
            container->root = node->left;
            node->left = parent;
        } else if (node->right != 0) {
            container->root = node->right;
            node->right = parent;
        }
        if (container->root != 0)
            container->root->parent = 0;
    } else {
        if (parent->left == node)
            parent->left = 0;
        else if (parent->right == node)
            parent->right = 0;
        node->parent = 0;
    }
    {
        if (node->left != 0) {
            cursor = container->root;
            subtree = node->left;
            ordering_value = subtree->ordering_value;
        find_left_slot:
            if (ordering_value < cursor->ordering_value) {
                next = cursor->left;
                if (next == 0) {
                    cursor->left = subtree;
                    goto left_attached;
                }
            } else {
                next = cursor->right;
                if (next == 0)
                    goto left_attach_right;
            }
            cursor = next;
            goto find_left_slot;
        left_attach_right:
            cursor->right = subtree;
        left_attached:
            subtree->parent = cursor;
            node->left = 0;
        }
    }
    {
        if (node->right != 0) {
            cursor = container->root;
            subtree = node->right;
            ordering_value = subtree->ordering_value;
        find_right_slot:
            if (ordering_value < cursor->ordering_value) {
                next = cursor->left;
                if (next == 0) {
                    cursor->left = subtree;
                    goto right_attached;
                }
            } else {
                next = cursor->right;
                if (next == 0)
                    goto right_attach_right;
            }
            cursor = next;
            goto find_right_slot;
        right_attach_right:
            cursor->right = subtree;
        right_attached:
            subtree->parent = cursor;
            node->right = 0;
        }
    }
    node->parent = 0;
}
