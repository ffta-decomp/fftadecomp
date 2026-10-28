#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern void *DefinitionRecordIdentity(void *);
extern u32 ApplyDefinitionValue(void *,u16,s8);
void ApplyDefinitionRecordSignedValue(void *record, u16 value, u8 selector)
{
    record = DefinitionRecordIdentity(record);
    ApplyDefinitionValue(record, value, (s8)selector);
}

asm(".global DefinitionRecordIdentity\n.thumb_set DefinitionRecordIdentity,0x80dd351\n"
    ".global ApplyDefinitionValue\n.thumb_set ApplyDefinitionValue,0x809a2d9\n");
