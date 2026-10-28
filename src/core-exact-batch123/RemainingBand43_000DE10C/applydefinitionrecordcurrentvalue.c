#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern void *DefinitionRecordIdentity(void *);
extern void ApplyDefinitionRecordSignedValue(void *,u16,s8);
void ApplyDefinitionRecordCurrentValue(void *record, u16 value)
{
    void *view = DefinitionRecordIdentity(record);
    ApplyDefinitionRecordSignedValue(record, value, ((const s8 *)view)[31]);
}

asm(".global DefinitionRecordIdentity\n.thumb_set DefinitionRecordIdentity,0x80dd351\n"
    ".global ApplyDefinitionRecordSignedValue\n.thumb_set ApplyDefinitionRecordSignedValue,0x80de12d\n");
