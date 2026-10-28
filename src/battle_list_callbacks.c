typedef unsigned int u32;

struct ListOwner;
extern void *GetListOwnerWord0(const struct ListOwner *owner);
extern u32 BattleListNodeVisitCallback(void *node, void *context);
extern void VisitLinkedNodes(const struct ListOwner *owner,
                             u32 (*visit)(void *node, void *context),
                             void *context);

/* The list-owner word selects the state used by this battle visitor. */
struct BattleListVisitState {
    u32 unknown_at_00;
    const struct ListOwner *list;
    u32 unknown_at_08;
    u32 active_flag;
};

u32 ResetAndVisitBattleList(const struct ListOwner *owner, void *unused_context)
{
    struct BattleListVisitState *state = GetListOwnerWord0(owner);
    state->active_flag = 0;
    VisitLinkedNodes(state->list, BattleListNodeVisitCallback, state);
    return 1;
}
