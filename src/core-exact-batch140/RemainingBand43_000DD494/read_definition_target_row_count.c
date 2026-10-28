#include "../../../src/task_tree_core.h"

extern u32 ReadBattleTargetRowCount(const void *);

u32 ReadDefinitionTargetRowCount(const void *record)
{
    return (u8)ReadBattleTargetRowCount(record);
}

__asm__(".global ReadBattleTargetRowCount\n"
        ".thumb_set ReadBattleTargetRowCount,0x080a8831\n");
