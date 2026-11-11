typedef unsigned char u8;
typedef unsigned int u32;
struct BattleSubmissionContext;
extern struct BattleSubmissionContext BattleSubmission;
extern u32 AdvanceBattleSubmission(struct BattleSubmissionContext *context, u32 mode);
__asm__(".global BattleSubmission\n.set BattleSubmission,0x020158b0\n.global AdvanceBattleSubmission\n.thumb_set AdvanceBattleSubmission,0x080c7079");
/* C09 selector42 waits until the real submission state machine completes. */
u32 PollBattleRecordSubmission(void)
{
    return (u8)AdvanceBattleSubmission(&BattleSubmission, 1);
}
