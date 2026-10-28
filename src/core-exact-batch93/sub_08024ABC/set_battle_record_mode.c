typedef unsigned char u8;
struct BattleModeRecord {
    u8 unknown_0000[4];
    u8 mode;
    u8 unknown_0005[5];
    u8 update_pending;
};
void SetBattleRecordMode(struct BattleModeRecord *record, u8 mode)
{
    record->mode = mode;
    if (mode == 0 || mode == 4)
        record->update_pending = 1;
}
