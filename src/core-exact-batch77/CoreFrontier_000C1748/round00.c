typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
union BattleRecordCount {
    u8 value;
    struct { u8 preserved : 4; u8 count : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
/* The index is a nibble. This union preserves overlap with the fixed fields. */
union BattleActionWindow {
    u8 tags[16];
    struct {
        u8 prefix[4];
        union BattleRecordCount count;
        u8 intervening[7];
        u16 action;
    } fields;
};
struct BattleActionRecordView { u8 prefix[0x54cc]; union BattleActionWindow window; };
typedef char CountByteSize[sizeof(union BattleRecordCount) == 1 ? 1 : -1];
typedef char CountOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.count == 0x54d0 ? 1 : -1];
typedef char ActionOffset[(u32)&((struct BattleActionRecordView *)0)->window.fields.action == 0x54d8 ? 1 : -1];
extern struct BattleActionRecordView gBattleActionRecordView;
__asm__(".global gBattleActionRecordView\n.set gBattleActionRecordView,0x020101f8");
void AppendBattlePreparedActionTag(void)
{
    union BattleRecordCount old_count;
    old_count = gBattleActionRecordView.window.fields.count;
    gBattleActionRecordView.window.fields.count.fields.count = old_count.fields.count + 1;
    gBattleActionRecordView.window.tags[old_count.fields.count] = 4;
}
