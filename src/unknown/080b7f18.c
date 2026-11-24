typedef unsigned char u8;
typedef unsigned short u16;
struct BattleRecordFlagView {
    u8 unknown_0000[4370];
    u16 flags;
};

void SetBattleRecordFlagEight(struct BattleRecordFlagView *record, u8 enabled)
{
    if (enabled)
        record->flags |= 0x100;
    else
        record->flags &= (u16)~0x100;
}
