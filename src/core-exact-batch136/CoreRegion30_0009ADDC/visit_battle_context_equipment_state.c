#include "../../../src/task_tree_core.h"
struct BattleUnitContextPrefix { u8 *unit; };
extern void ApplyEquippedItemStateBits(u8 *unit);
u32 VisitBattleContextEquipmentState(u32 owner_word, void *unused_argument)
{
    struct BattleUnitContextPrefix *context = (struct BattleUnitContextPrefix *)owner_word;
    ApplyEquippedItemStateBits(context->unit);
    return 1;
}
asm(".global ApplyEquippedItemStateBits\n.thumb_set ApplyEquippedItemStateBits,0x0812ed59\n");
