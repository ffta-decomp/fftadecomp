struct BattleSelection;
struct Actor;
extern struct BattleSelection gCurrentBattleSelection;
extern void InitializeBattleSelection(struct BattleSelection *selection, struct Actor *actor);
__asm__(".global gCurrentBattleSelection\n.set gCurrentBattleSelection,0x020101f8\n.global InitializeBattleSelection\n.thumb_set InitializeBattleSelection,0x080c034d");
void InitializeCurrentBattleSelection(struct Actor *actor)
{
    InitializeBattleSelection(&gCurrentBattleSelection, actor);
}
