typedef unsigned char u8;
struct BattleRecord {
    u8 unknown_000[26];
    u8 field_01a;
};
extern void ConfigureBattleRecordDisplay(u8 first_selector, u8 second_selector);
__asm__(".global ConfigureBattleRecordDisplay\n.thumb_set ConfigureBattleRecordDisplay, 0x08022ba5");

/* Field meaning is unresolved; its byte clear follows the real display service. */
void ResetBattleRecordDisplayState(struct BattleRecord *record)
    __asm__("CoreFrontier_0009A624");
void ResetBattleRecordDisplayState(struct BattleRecord *record)
{
    ConfigureBattleRecordDisplay(1, 2);
    record->field_01a = 0;
}
