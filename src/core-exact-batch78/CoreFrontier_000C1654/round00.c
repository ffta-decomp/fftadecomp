typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
union BattleRecordCount {
    u8 value;
    struct { u8 option : 4; u8 count : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
union BattleRecordPosition {
    u8 value;
    struct { u8 x : 4; u8 y : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
/* Actual tag-index window overlaps the fixed action fields. */
union BattleActionWindow {
    u8 tags[16];
    struct {
        u8 prefix[4];
        union BattleRecordCount count;
        u8 intervening5;
        union BattleRecordPosition position;
        u8 intervening7;
        union BattleRecordCount advance;
        u8 intervening9[3];
        u16 action;
        u16 equipment;
    } fields;
};
struct BattleActionRecordView { u8 prefix[0x54cc]; union BattleActionWindow window; };
typedef char CountSize[sizeof(union BattleRecordCount) == 1 ? 1 : -1];
typedef char PositionSize[sizeof(union BattleRecordPosition) == 1 ? 1 : -1];
typedef char CountOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.count == 0x54d0 ? 1 : -1];
typedef char PositionOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.position == 0x54d2 ? 1 : -1];
typedef char AdvanceOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.advance == 0x54d4 ? 1 : -1];
typedef char ActionOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.action == 0x54d8 ? 1 : -1];
typedef char EquipmentOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.equipment == 0x54da ? 1 : -1];
extern struct BattleActionRecordView gBattleActionRecordView;
__asm__(".global gBattleActionRecordView\n.set gBattleActionRecordView,0x020101f8");
void RecordBattleActionRequestTag(u8 x, u8 y, u32 action, u32 equipment, u8 option)
{
    union BattleRecordCount old_count;
    gBattleActionRecordView.window.fields.position.fields.x = x;
    gBattleActionRecordView.window.fields.position.fields.y = y;
    gBattleActionRecordView.window.fields.action = action;
    gBattleActionRecordView.window.fields.equipment = equipment;
    gBattleActionRecordView.window.fields.advance.fields.option = option;
    old_count = gBattleActionRecordView.window.fields.count;
    gBattleActionRecordView.window.fields.count.fields.count = old_count.fields.count + 1;
    gBattleActionRecordView.window.tags[old_count.fields.count] = 3;
}
