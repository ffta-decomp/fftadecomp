typedef unsigned char u8;
typedef unsigned int u32;
struct BattlePhaseContinuation { u8 state[136]; };
extern void *AllocateBattlePhaseBytes(u32 bytes);
extern void InitializeBattlePhaseContinuation(struct BattlePhaseContinuation *record,
                                              u32 source_context);
struct BattlePhaseContinuation *CreateBattlePhaseContinuation(u32 source_context)
{
    struct BattlePhaseContinuation *record = AllocateBattlePhaseBytes(136);
    InitializeBattlePhaseContinuation(record, source_context);
    return record;
}
asm(".global AllocateBattlePhaseBytes\n.thumb_set AllocateBattlePhaseBytes,0x08022841\n"
    ".global InitializeBattlePhaseContinuation\n.thumb_set InitializeBattlePhaseContinuation,0x080BC4BD\n");
