typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleUnitPosition { u8 prefix[246]; u8 x, y; };
struct BattlePositionNode {
    struct BattleUnitPosition *unit;
    u8 gap4[4];
    u16 position_x;
    u8 gap10[2];
    u16 position_y;
};
typedef char UnitXOffset[(u32)&((struct BattleUnitPosition *)0)->x == 246 ? 1 : -1];
typedef char UnitYOffset[(u32)&((struct BattleUnitPosition *)0)->y == 247 ? 1 : -1];
typedef char NodeXOffset[(u32)&((struct BattlePositionNode *)0)->position_x == 8 ? 1 : -1];
typedef char NodeYOffset[(u32)&((struct BattlePositionNode *)0)->position_y == 12 ? 1 : -1];
extern void FindBattleProbePosition(void *battle, struct BattlePositionNode *previous,
    struct BattlePositionNode *current, u8 *x_out, u8 *y_out, u8 *direction_out);
__asm__(".global FindBattleProbePosition\n.thumb_set FindBattleProbePosition,0x080c127d");
void ProbeBattlePositionAtNodeCoordinates(void *battle, struct BattlePositionNode *previous,
    struct BattlePositionNode *current, u8 *x_out, u8 *y_out, u8 *direction_out)
{
    struct BattleUnitPosition *entry_unit = current->unit;
    u8 old_x = entry_unit->x;
    u8 old_y = entry_unit->y;
    entry_unit->x = current->position_x >> 5;
    current->unit->y = current->position_y >> 5;
    FindBattleProbePosition(battle, previous, current, x_out, y_out, direction_out);
    current->unit->x = old_x;
    current->unit->y = old_y;
}
