#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern u32 ApplyRecordTransition(void *,u16,int,u16);
void ApplyDefinitionRecordTransition(void *record, u16 first, u16 second)
{
    ApplyRecordTransition(record, first, ((const s8 *)record)[31], second);
}

asm(".global ApplyRecordTransition\n.thumb_set ApplyRecordTransition,0x809836d\n");
