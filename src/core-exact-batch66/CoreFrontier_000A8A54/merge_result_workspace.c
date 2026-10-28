struct BattleResultWorkspace;
struct BattleActionResults;
extern void AppendActionResultEntries(struct BattleActionResults *source,
                                      struct BattleResultWorkspace *target);
/* Selector64 appends a second action result only when both records exist. */
void MergeBattleActionResultWorkspace(struct BattleResultWorkspace *target,
                                      struct BattleActionResults *source)
{
    AppendActionResultEntries(source, target);
}
asm(".global AppendActionResultEntries\n.thumb_set AppendActionResultEntries,0x080A7A81\n");
