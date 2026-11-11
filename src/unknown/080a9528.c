struct BattlePositionRecord;
extern void ResetBattlePositionRecord(struct BattlePositionRecord *record);
__asm__(".global ResetBattlePositionRecord\n.thumb_set ResetBattlePositionRecord, 0x080a8fbd");

/* Pass the fixed record address itself, preserving the real reset transition. */
void ResetGlobalBattlePositionRecord(void) __asm__("CoreConsumer_000A9528");
void ResetGlobalBattlePositionRecord(void)
{
    ResetBattlePositionRecord((struct BattlePositionRecord *)0x0200ffc8);
}
