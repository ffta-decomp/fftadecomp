#include "../../../src/task_tree_core.h"

struct BattleUnitFieldView;
struct DefinitionUnitRecordPrefix { const struct BattleUnitFieldView *unit; };
extern u32 ReadUnitField(const struct BattleUnitFieldView *,u8);
u32 ReadDefinitionUnitFieldThree(const struct DefinitionUnitRecordPrefix *record)
{
    return (u16)ReadUnitField(record->unit,3);
}
asm(".global ReadUnitField\n.thumb_set ReadUnitField,0x080c7ea5\n");
