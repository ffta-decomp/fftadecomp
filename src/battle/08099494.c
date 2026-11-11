typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

extern int CollectContextListPayloadsAt10(const u8 *context, u8 **nodes);
asm(".global CollectContextListPayloadsAt10\n.thumb_set CollectContextListPayloadsAt10, 0x08099cdd");
extern u8 UnitStateEAHasBit3(const u8 *unit);
asm(".global UnitStateEAHasBit3\n.thumb_set UnitStateEAHasBit3, 0x080cdbcd");
extern u8 ReadUnitCounterE6(const u8 *unit);
asm(".global ReadUnitCounterE6\n.thumb_set ReadUnitCounterE6, 0x080ce411");
extern u8 CanBattleUnitTakeTurn(const u8 *unit);
asm(".global CanBattleUnitTakeTurn\n.thumb_set CanBattleUnitTakeTurn, 0x0812e4a9");

u8 *SelectEligibleContextListNode(const u8 *context, u8 **selected_unit)
{
    u8 *nodes[13];
    int count = CollectContextListPayloadsAt10(context, nodes);
    u8 *chosen = 0;
    int lowest = 1024;
    int index;

    for (index = 0; index < count; index++) {
        u8 *node = nodes[index];
        s16 score = *(s16 *)(node + 92);
        if (score < lowest) {
            u8 *unit = *(u8 **)node;
            if (UnitStateEAHasBit3(unit)) {
                const u8 *wanted = *selected_unit + 260;
                unsigned int actual = ReadUnitCounterE6(*(u8 **)nodes[index]);
                if (*wanted == (u8)actual &&
                    CanBattleUnitTakeTurn(*(u8 **)nodes[index])) {
                    lowest = *(s16 *)(nodes[index] + 92);
                    chosen = nodes[index];
                }
            }
        }
    }
    return chosen;
}
