struct BattleRouteRecord;
extern void FreeBattleRouteAllocation(void *record);
void ReleaseBattleRouteRecord(struct BattleRouteRecord *record)
{
    FreeBattleRouteAllocation(record);
}
asm(".global FreeBattleRouteAllocation\n.thumb_set FreeBattleRouteAllocation,0x08022855\n");
