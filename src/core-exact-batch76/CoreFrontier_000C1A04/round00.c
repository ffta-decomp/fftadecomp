typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
union BattlePackedTarget {
    u8 value;
    struct { u8 x : 4; u8 y : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
/* These packed requests are distinct from the earlier raw-coordinate fields. */
struct BattleActionRequests {
    u8 prefix[0x54d2];
    union BattlePackedTarget first_target;
    union BattlePackedTarget second_target;
    u8 intervening[8];
    u16 first_action;
    u16 second_action;
};
typedef char TargetByteSize[sizeof(union BattlePackedTarget) == 1 ? 1 : -1];
typedef char FirstTargetOffset[(u32)&((struct BattleActionRequests *)0)->first_target == 0x54d2 ? 1 : -1];
typedef char SecondTargetOffset[(u32)&((struct BattleActionRequests *)0)->second_target == 0x54d3 ? 1 : -1];
typedef char FirstActionOffset[(u32)&((struct BattleActionRequests *)0)->first_action == 0x54dc ? 1 : -1];
typedef char SecondActionOffset[(u32)&((struct BattleActionRequests *)0)->second_action == 0x54de ? 1 : -1];
extern struct BattleActionRequests gBattleActionRequests;
__asm__(".global gBattleActionRequests\n.set gBattleActionRequests,0x020101f8");
void StoreBattleActionRequest(u8 slot, u16 action, u8 x, u8 y)
{
    if (slot == 0) {
        gBattleActionRequests.first_target.fields.x = x;
        gBattleActionRequests.first_target.fields.y = y;
        gBattleActionRequests.first_action = action;
    } else {
        gBattleActionRequests.second_target.fields.x = x;
        gBattleActionRequests.second_target.fields.y = y;
        gBattleActionRequests.second_action = action;
    }
}
