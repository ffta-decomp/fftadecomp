typedef unsigned char u8;
typedef unsigned int u32;

struct BattleOutcomeContinuation {
    u32 content;
    void *unit;
    u8 remaining_state[448];
};
typedef char BattleOutcomeContinuationSize[(sizeof(struct BattleOutcomeContinuation) == 456) ? 1 : -1];
typedef void (*ClearBattleContinuationBytes)(void *, u32);
extern void *AllocateBattleContinuationBytes(u32 bytes);
extern void *FindBattleUnitForContent(u32 content);
__asm__(".global AllocateBattleContinuationBytes\n.thumb_set AllocateBattleContinuationBytes,0x08022841\n"
        ".global FindBattleUnitForContent\n.thumb_set FindBattleUnitForContent,0x08099545\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

struct BattleOutcomeContinuation *CreateBattleOutcomeContinuation(u32 content)
    __asm__("CoreFrontier_000BC950");

/* The phase controller retains this record while waiting for outcome handling. */
struct BattleOutcomeContinuation *CreateBattleOutcomeContinuation(u32 content)
{
    struct BattleOutcomeContinuation *output = AllocateBattleContinuationBytes(456);
    (*(ClearBattleContinuationBytes *)0x0836d4b8)(output, 456);
    output->unit = FindBattleUnitForContent(content);
    output->content = content;
    return output;
}
