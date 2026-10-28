#include "interfaces.h"

route_u32 QueryBattleRouteNodePending(void *context, void *node)
{
    struct RoutePendingQuery query;
    if (node == 0)
        return 0;
    query.reference_node = node;
    query.pending = 0;
    RetailCall_08099840(context, AccumulateBattleRouteNodePending, &query);
    return query.pending;
}
