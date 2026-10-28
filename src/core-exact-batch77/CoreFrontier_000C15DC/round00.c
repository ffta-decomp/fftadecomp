typedef unsigned char u8;
typedef unsigned int u32;
union BattleRecordCount {
    u8 value;
    struct { u8 option : 4; u8 count : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
union BattleRecordPosition {
    u8 value;
    struct { u8 x : 4; u8 y : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
/* The tag nibble's address window overlaps the fixed fields intentionally. */
union BattleRecordWindow {
    u8 tags[16];
    struct {
        u8 prefix[4];
        union BattleRecordCount count;
        union BattleRecordPosition position;
        u8 remaining[10];
    } fields;
};
struct BattleActionRecordView { u8 prefix[0x54cc]; union BattleRecordWindow window; };
typedef char CountSize[sizeof(union BattleRecordCount) == 1 ? 1 : -1];
typedef char PositionSize[sizeof(union BattleRecordPosition) == 1 ? 1 : -1];
typedef char CountOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.count == 0x54d0 ? 1 : -1];
typedef char PositionOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.position == 0x54d1 ? 1 : -1];
extern struct BattleActionRecordView gBattleActionRecordView;
__asm__(".global gBattleActionRecordView\n.set gBattleActionRecordView,0x020101f8");
void RecordBattlePositionTag(u8 x, u8 y, u8 option)
{
    union BattleRecordCount old_count;
    gBattleActionRecordView.window.fields.position.fields.x = x;
    gBattleActionRecordView.window.fields.position.fields.y = y;
    gBattleActionRecordView.window.fields.count.fields.option = option;
    old_count = gBattleActionRecordView.window.fields.count;
    gBattleActionRecordView.window.fields.count.fields.count = old_count.fields.count + 1;
    gBattleActionRecordView.window.tags[old_count.fields.count] = 2;
}
