#ifndef FFTA_BATTLE_SCENE_ROUTE_LIFECYCLE_18_H
#define FFTA_BATTLE_SCENE_ROUTE_LIFECYCLE_18_H

typedef unsigned char route_u8;
typedef signed char route_s8;
typedef unsigned short route_u16;
typedef signed short route_s16;
typedef unsigned int route_u32;
typedef signed int route_s32;

#define RouteByte(base, offset) (*(volatile route_u8 *)((route_u8 *)(base) + (offset)))
#define RouteHalf(base, offset) (*(volatile route_u16 *)((route_u8 *)(base) + (offset)))
#define RouteSignedHalf(base, offset) (*(volatile route_s16 *)((route_u8 *)(base) + (offset)))
#define RouteWord(base, offset) (*(volatile route_u32 *)((route_u8 *)(base) + (offset)))
#define RoutePointer(base, offset) (*(void * volatile *)((route_u8 *)(base) + (offset)))

struct RoutePendingQuery {
    void * volatile reference_node;
    volatile route_u32 pending;
};

typedef route_u32 (*RouteNodeVisitor)(void *node, struct RoutePendingQuery *query);

void InitializeBattleRouteRecord(void *record, void *node, route_u8 *route, route_s32 length);
void ApplyBattleRouteEndpointPolicy(void *record);
route_u32 CheckBattleRouteAdjustment(void *node, route_u8 *route,
    route_s32 length, route_s32 upper_step, route_s32 lower_step);
route_u32 GetBattleRouteAdjustmentFlag(void *record);
route_u32 QueryBattleRouteNodePending(void *context, void *node);
route_u32 AccumulateBattleRouteNodePending(void *node, struct RoutePendingQuery *query);

extern route_u32 RetailCall_0809a53c(void *node);
extern void RetailCall_0809836c(void *node, route_u32 operation, route_s32 direction, route_u32 value);
extern void RetailCall_0809a570(void *node, route_u32 first, route_u32 second);
extern route_u32 RetailCall_08148a98(route_u8 *route, route_s32 length);
extern void *RetailCall_08099644(void *context, route_s32 x, route_s32 y);
extern const volatile route_u8 *RetailCall_080c7ea4(void *unit, route_u32 property);
extern route_s32 RetailCall_08099c1c(void *node, route_s32 x, route_s32 y);
extern route_u32 RetailCall_080c8240(void *unit);
extern route_u32 RetailCall_080ca3ec(void *unit);
extern route_u32 RetailCall_08142ab0(route_u32 numerator, route_u32 denominator);
extern route_u32 RetailCall_0801cd08(route_u32 x, route_u32 y);
extern void RetailCall_08099840(void *context, RouteNodeVisitor visitor, struct RoutePendingQuery *query);
extern route_u32 RetailCall_080cdadc(void *unit);
extern route_u32 RetailCall_080cdb24(void *unit);
extern route_u32 RetailCall_080cd92c(void *unit);
extern route_u32 RetailCall_0809c8c8(void *node, route_u32 step);
extern void RetailCall_0809c6b8(route_u32 direction, void *node, route_u32 amount);

#endif
