typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct RoutePoint { u8 x, y, z, flags; };
struct BattleRouteRecord {
    void *node;
    struct RoutePoint *route;
    u16 start_x, start_z, start_y, reserved14;
    u16 target_x, target_z, target_y, reserved22;
    s16 count, index;
    u8 reserved28[11];
    u8 facing;
};
#define FIELD_AT(type,member,value) typedef char guard_##member[((u32)&(((type *)0)->member)==value)?1:-1]
FIELD_AT(struct BattleRouteRecord,route,4);
FIELD_AT(struct BattleRouteRecord,start_x,8);
FIELD_AT(struct BattleRouteRecord,target_x,16);
FIELD_AT(struct BattleRouteRecord,count,24);
FIELD_AT(struct BattleRouteRecord,index,26);
FIELD_AT(struct BattleRouteRecord,facing,39);
typedef char point_stride4[(sizeof(struct RoutePoint)==4)?1:-1];
typedef char record_size40[(sizeof(struct BattleRouteRecord)==40)?1:-1];
