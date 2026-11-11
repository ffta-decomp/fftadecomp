struct BattleActionRegistry;
extern struct BattleActionRegistry *gBattleActionRegistry;
/* Return the exact stored word; callers own its null and layout contracts. */
struct BattleActionRegistry *GetContentConsumerContext(void)
{
    return gBattleActionRegistry;
}
asm(".global gBattleActionRegistry\n.set gBattleActionRegistry,0x0200F4B0\n");
