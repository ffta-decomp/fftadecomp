#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern u32 PollBattleRecordHandles(void *);
u32 PollDefinitionRecordHandles(void *record)
{
    return (u8)PollBattleRecordHandles(record);
}

asm(".global PollBattleRecordHandles\n.thumb_set PollBattleRecordHandles,0x8099c65\n");
