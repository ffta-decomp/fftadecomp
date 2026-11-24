typedef unsigned char u8;
typedef unsigned int u32;
struct TreeNode;
struct Container;
struct BattleTreeVisitView { u8 unknown0[80]; struct Container *tree; u8 unknown84[1416]; u8 enabled; };
typedef char TreeAt80[(u32)&((struct BattleTreeVisitView *)0)->tree == 80 ? 1 : -1];
typedef char EnabledAt1500[(u32)&((struct BattleTreeVisitView *)0)->enabled == 1500 ? 1 : -1];
typedef u32 (*TreeVisitor)(struct TreeNode *, void *);
extern void TraverseBattleTreeReverse(struct Container *, TreeVisitor, void *);
extern u32 UpdateBattleTreeNode(struct TreeNode *, void *workspace);
__asm__(".global TraverseBattleTreeReverse\n.thumb_set TraverseBattleTreeReverse,0x080c7d71\n.global UpdateBattleTreeNode\n.thumb_set UpdateBattleTreeNode,0x080a8e0d");
void UpdateEnabledBattleTree(void)
{
    register struct BattleTreeVisitView *workspace __asm__("r2") = (struct BattleTreeVisitView *)0x0200f9e8;
    /* Retain the original base for the guard, tree load and callback userdata. */
    __asm__("" : "+r" (workspace));
    if (workspace->enabled != 0)
        TraverseBattleTreeReverse(workspace->tree, UpdateBattleTreeNode, workspace);
}
