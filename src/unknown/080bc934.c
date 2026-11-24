typedef unsigned char u8;
typedef unsigned int u32;
extern u32 AdvanceBattlePhaseRecord(void *record);
asm(".global AdvanceBattlePhaseRecord\n.thumb_set AdvanceBattlePhaseRecord,0x080bbc39");

u8 PollBattlePhaseRecord(void *record)
{
    return (u8)AdvanceBattlePhaseRecord(record);
}
