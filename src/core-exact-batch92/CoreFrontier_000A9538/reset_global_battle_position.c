/* Battle C09 transition adapter. The callee owns the position reset effects. */
extern void ResetBattlePositionRecord(void *record);
__asm__(".global ResetBattlePositionRecord\n.thumb_set ResetBattlePositionRecord,0x080a8f61");

void ResetGlobalBattlePosition(void) __asm__("CoreFrontier_000A9538");
void ResetGlobalBattlePosition(void)
{
    ResetBattlePositionRecord((void *)0x0200ffc8);
}
