typedef unsigned int u32;
struct TreeNode;
struct Container { void *pool; void *list; struct TreeNode *root; };
struct Collection { struct TreeNode **cursor; u32 count; };
typedef u32 (*CollectionVisitor)(struct TreeNode *, struct Collection *);
extern u32 AppendCollectedNode(struct TreeNode *, struct Collection *);
extern void TraverseCollectedNodes(struct Container *, CollectionVisitor, struct Collection *);
__asm__(".global AppendCollectedNode\n.thumb_set AppendCollectedNode,0x080c7e69\n.global TraverseCollectedNodes\n.thumb_set TraverseCollectedNodes,0x080c7d19");
u32 TreeCollectInOrder(struct Container *container, struct TreeNode **output)
{
    struct Collection collection;
    u32 result;
    if (container->root != 0) {
        collection.cursor = output;
        collection.count = 0;
        TraverseCollectedNodes(container, AppendCollectedNode, &collection);
        result = collection.count;
    } else {
        result = 0;
    }
    return result;
}
