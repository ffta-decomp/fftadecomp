typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRecordWorkset;
extern u32 StepExistingBattleWorkset(struct BattleRecordWorkset *);
u8 PollBattleRecordWorkset(struct BattleRecordWorkset *workset)
{
    return (u8)StepExistingBattleWorkset(workset);
}
asm(".global StepExistingBattleWorkset\n.thumb_set StepExistingBattleWorkset,0x080bd8cd\n");
