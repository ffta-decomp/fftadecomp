typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
union BattleNibbles {
    u8 value;
    struct { u8 low : 4; u8 high : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
/* Partial live raw-input/packed-output view; unnamed gaps have no inferred role. */
struct BattleRecordPackingView {
    u8 prefix[0x54b0];
    u8 raw_first_x, raw_first_y;
    u8 raw_second_x, raw_second_y;
    u8 raw_position_x, raw_position_y;
    u8 gap_b6[4];
    u8 raw_value, raw_option;
    u8 gap_bc[2];
    u16 raw_action, raw_equipment;
    u16 raw_first_action, raw_second_action;
    u8 gap_c6[6];
    u8 tags[4];
    union BattleNibbles count;
    union BattleNibbles position;
    union BattleNibbles first_target;
    union BattleNibbles second_target;
    union BattleNibbles advance;
    u8 action_option;
    u8 gap_d6[2];
    u16 action, equipment;
    u16 first_action, second_action;
    u32 seed;
    u8 raw_tags[4];
    u8 raw_count;
};
typedef char NibbleByteSize[sizeof(union BattleNibbles) == 1 ? 1 : -1];
typedef char Offset_raw_first_x[(u32)&((struct BattleRecordPackingView *)0)->raw_first_x == 0x54b0 ? 1 : -1];
typedef char Offset_raw_second_x[(u32)&((struct BattleRecordPackingView *)0)->raw_second_x == 0x54b2 ? 1 : -1];
typedef char Offset_raw_position_x[(u32)&((struct BattleRecordPackingView *)0)->raw_position_x == 0x54b4 ? 1 : -1];
typedef char Offset_raw_value[(u32)&((struct BattleRecordPackingView *)0)->raw_value == 0x54ba ? 1 : -1];
typedef char Offset_raw_option[(u32)&((struct BattleRecordPackingView *)0)->raw_option == 0x54bb ? 1 : -1];
typedef char Offset_raw_action[(u32)&((struct BattleRecordPackingView *)0)->raw_action == 0x54be ? 1 : -1];
typedef char Offset_raw_equipment[(u32)&((struct BattleRecordPackingView *)0)->raw_equipment == 0x54c0 ? 1 : -1];
typedef char Offset_raw_first_action[(u32)&((struct BattleRecordPackingView *)0)->raw_first_action == 0x54c2 ? 1 : -1];
typedef char Offset_raw_second_action[(u32)&((struct BattleRecordPackingView *)0)->raw_second_action == 0x54c4 ? 1 : -1];
typedef char Offset_tags[(u32)&((struct BattleRecordPackingView *)0)->tags == 0x54cc ? 1 : -1];
typedef char Offset_count[(u32)&((struct BattleRecordPackingView *)0)->count == 0x54d0 ? 1 : -1];
typedef char Offset_position[(u32)&((struct BattleRecordPackingView *)0)->position == 0x54d1 ? 1 : -1];
typedef char Offset_first_target[(u32)&((struct BattleRecordPackingView *)0)->first_target == 0x54d2 ? 1 : -1];
typedef char Offset_second_target[(u32)&((struct BattleRecordPackingView *)0)->second_target == 0x54d3 ? 1 : -1];
typedef char Offset_advance[(u32)&((struct BattleRecordPackingView *)0)->advance == 0x54d4 ? 1 : -1];
typedef char Offset_action[(u32)&((struct BattleRecordPackingView *)0)->action == 0x54d8 ? 1 : -1];
typedef char Offset_equipment[(u32)&((struct BattleRecordPackingView *)0)->equipment == 0x54da ? 1 : -1];
typedef char Offset_first_action[(u32)&((struct BattleRecordPackingView *)0)->first_action == 0x54dc ? 1 : -1];
typedef char Offset_second_action[(u32)&((struct BattleRecordPackingView *)0)->second_action == 0x54de ? 1 : -1];
typedef char Offset_raw_tags[(u32)&((struct BattleRecordPackingView *)0)->raw_tags == 0x54e4 ? 1 : -1];
typedef char Offset_raw_count[(u32)&((struct BattleRecordPackingView *)0)->raw_count == 0x54e8 ? 1 : -1];
extern struct BattleRecordPackingView gBattleRecordPackingView;
extern void (*const CopyBattleRecordBytes)(void *destination, const void *source, u32 bytes);
__asm__(".global gBattleRecordPackingView\n.set gBattleRecordPackingView,0x020101f8\n.global CopyBattleRecordBytes\n.set CopyBattleRecordBytes,0x0836d4bc\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
void PackCurrentBattleActionRecord(void)
{
    gBattleRecordPackingView.count.fields.low = gBattleRecordPackingView.raw_value;
    gBattleRecordPackingView.first_target.fields.low = gBattleRecordPackingView.raw_second_x;
    gBattleRecordPackingView.first_target.fields.high = gBattleRecordPackingView.raw_second_y;
    gBattleRecordPackingView.position.fields.low = gBattleRecordPackingView.raw_position_x;
    gBattleRecordPackingView.position.fields.high = gBattleRecordPackingView.raw_position_y;
    gBattleRecordPackingView.action = gBattleRecordPackingView.raw_action;
    gBattleRecordPackingView.equipment = gBattleRecordPackingView.raw_equipment;
    gBattleRecordPackingView.advance.fields.low = gBattleRecordPackingView.raw_option;
    gBattleRecordPackingView.second_target.fields.low = gBattleRecordPackingView.raw_first_x;
    gBattleRecordPackingView.second_target.fields.high = gBattleRecordPackingView.raw_first_y;
    gBattleRecordPackingView.first_action = gBattleRecordPackingView.raw_first_action;
    gBattleRecordPackingView.second_action = gBattleRecordPackingView.raw_second_action;
    CopyBattleRecordBytes(gBattleRecordPackingView.tags, gBattleRecordPackingView.raw_tags, 4);
    /* The real helper may modify either source count or the preserved low nibble. */
    gBattleRecordPackingView.count.fields.high = gBattleRecordPackingView.raw_count;
}
