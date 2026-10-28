typedef unsigned int u32;
struct TreeNode;
struct TreeContainer { void *pool; void *list; struct TreeNode *root; };
struct TreeSearch { u32 word; struct TreeNode *found; };
typedef u32 (*TreeSearchVisitor)(struct TreeNode *, struct TreeSearch *);
typedef char SearchSize8[sizeof(struct TreeSearch) == 8 ? 1 : -1];
/* The traversal's opaque user pointer is this concrete search object here. */
extern u32 MatchTreeNodeWord(struct TreeNode *node, struct TreeSearch *search);
extern void TraverseSearchTree(struct TreeContainer *container, TreeSearchVisitor callback, struct TreeSearch *search);
__asm__(".global MatchTreeNodeWord\n.thumb_set MatchTreeNodeWord,0x080c7e39\n.global TraverseSearchTree\n.thumb_set TraverseSearchTree,0x080c7d19");
struct TreeNode *TreeSearchByWord1(struct TreeContainer *container, u32 word)
{
    struct TreeSearch search;
    struct TreeNode *result;
    if (container->root != 0) {
        search.word = word;
        search.found = 0;
        TraverseSearchTree(container, MatchTreeNodeWord, &search);
        result = search.found;
    } else {
        result = 0;
    }
    return result;
}
