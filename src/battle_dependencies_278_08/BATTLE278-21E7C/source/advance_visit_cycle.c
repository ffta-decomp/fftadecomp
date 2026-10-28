typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct LinkedNode;
struct ListOwner;
typedef u32 (*ListVisitor)(void *, void *);
struct BattleVisitState {
    u32 unknown0;
    struct ListOwner *outer;
    struct ListOwner *inner;
    u8 unknown12[8];
    u8 context[448];
    u16 samples[3];
    u16 unknown474;
    s16 index;
    u16 cycle;
    u32 unknown480;
    u32 bookmark;
};
typedef char IndexOffset[(u32)&((struct BattleVisitState *)0)->index == 476 ? 1 : -1];
typedef char BookmarkOffset[(u32)&((struct BattleVisitState *)0)->bookmark == 484 ? 1 : -1];
extern struct LinkedNode *FindNode(struct ListOwner *, u32) __asm__("RetailCall_080c7bf4");
extern void VisitAll(struct ListOwner *, ListVisitor, void *) __asm__("RetailCall_080c7cc0");
extern void VisitFrom(struct ListOwner *, struct LinkedNode *, ListVisitor, void *) __asm__("RetailCall_080c7ce4");
extern u32 VisitInnerNode(void *, void *) __asm__("0x08021485");
extern u32 ResetOuterList(void *, void *) __asm__("0x08022129");

void SceneTaskDependency_00021E7C(struct BattleVisitState *state)
{
    struct LinkedNode *node;
    state->cycle = 0;
    if (state->index > 2)
        state->index = 0;
    if (state->bookmark != 0) {
        node = FindNode(state->inner, state->bookmark);
        if (node != 0)
            goto from_bookmark;
        state->bookmark = (u32)node;
    }
    VisitAll(state->inner, VisitInnerNode, state->context);
    goto visited_inner;
from_bookmark:
    state->bookmark = 0;
    VisitFrom(state->inner, node, VisitInnerNode, state->context);
visited_inner:
    VisitAll(state->outer, ResetOuterList, 0);
    state->index++;
    if (state->index > 2)
        state->index = 0;
    state->samples[state->index] = 0;
}

__asm__(".global RetailCall_080c7bf4\n.thumb_set RetailCall_080c7bf4,0x080c7bf5\n"
        ".global RetailCall_080c7cc0\n.thumb_set RetailCall_080c7cc0,0x080c7cc1\n"
        ".global RetailCall_080c7ce4\n.thumb_set RetailCall_080c7ce4,0x080c7ce5");
