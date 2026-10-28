typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Cleared span only; later controller fields retain provisional meanings. */
struct BattleActionSubmission {
    void *record;
    u8 intervening[96];
    u16 state;
    u8 remaining[70];
};
typedef char SubmissionSize[sizeof(struct BattleActionSubmission) == 172 ? 1 : -1];
typedef char StateOffset[(u32)&((struct BattleActionSubmission *)0)->state == 100 ? 1 : -1];
extern struct BattleActionSubmission gBattleActionSubmission;
extern void (*const ClearBattleActionMemory)(void *destination, u32 bytes);
__asm__(".global gBattleActionSubmission\n.set gBattleActionSubmission,0x020158b0\n.global ClearBattleActionMemory\n.set ClearBattleActionMemory,0x0836d4b8\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
void InitializeBattleActionSubmission(void *record)
{
    ClearBattleActionMemory(&gBattleActionSubmission, 172);
    gBattleActionSubmission.record = record;
    gBattleActionSubmission.state = 2;
}
