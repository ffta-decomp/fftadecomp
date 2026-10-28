typedef unsigned char u8;
typedef unsigned int u32;
struct BattleActionRecord { u8 action_type; u8 effect_selector; };
struct BattleEffectContext { u8 unknown00_to_2f[48]; const struct BattleActionRecord *action; };
typedef char ActionPointerOffset[((u32)&(((struct BattleEffectContext*)0)->action)==48)?1:-1];
extern struct BattleEffectContext gBattleEffectContext;
asm(".global gBattleEffectContext\n.set gBattleEffectContext,0x0200f3f0");
unsigned int ReadCurrentBattleActionType(void) asm("ActionDependency_00131024");
unsigned int ReadCurrentBattleActionType(void)
{
    return gBattleEffectContext.action->action_type;
}
