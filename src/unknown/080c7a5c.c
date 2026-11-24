struct TreeNode;
struct TreeContainer { void *pool; void *list; struct TreeNode *root; };
extern void DetachTreeNode(struct TreeContainer *container, struct TreeNode *node);
extern void ReleaseDetachedTreeNode(void *pool, void *node);
__asm__(".global DetachTreeNode\n.thumb_set DetachTreeNode,0x080c7859\n.global ReleaseDetachedTreeNode\n.thumb_set ReleaseDetachedTreeNode,0x08007171");
void DetachAndFreeTreeNode(struct TreeContainer *container, struct TreeNode *node)
{
    DetachTreeNode(container, node);
    ReleaseDetachedTreeNode(container->pool, node);
}
