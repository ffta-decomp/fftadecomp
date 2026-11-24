typedef unsigned int u32;
struct SelectedBattleActor;
struct BattlePhasePrefix { u32 unaccessed_word; struct SelectedBattleActor *actor; };
extern struct BattlePhasePrefix *gBattlePhase;
/* Both dereferences are unconditional, as in the original caller contract. */
struct SelectedBattleActor *GetContentContextPointerAt4(void)
{
    return gBattlePhase->actor;
}
asm(".global gBattlePhase\n.set gBattlePhase,0x0200F4A8\n");
