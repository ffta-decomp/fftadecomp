/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleOrderActor { const u8 *unit; u8 unknown_04[88]; u16 order_marker; };
typedef char OrderMarkerOffset[(u32)&((struct BattleOrderActor *)0)->order_marker == 92 ? 1 : -1];
extern u8 CanBattleUnitTakeTurn(const u8 *unit);
extern u8 UnitStateEBHasBit2(const u8 *unit);
extern u8 UnitStateEAHasBit7(const u8 *unit);


u32 InitializeBattleTurnOrderMarker(struct BattleOrderActor *actor, void *argument);
u32 InitializeBattleTurnOrderMarker(struct BattleOrderActor *actor, void *argument)
{
    if (!CanBattleUnitTakeTurn(actor->unit)
        || UnitStateEBHasBit2(actor->unit)
        || UnitStateEAHasBit7(actor->unit))
        actor->order_marker = 0xffff;
    else
        actor->order_marker = 0xfffe;
    return 1;
}
