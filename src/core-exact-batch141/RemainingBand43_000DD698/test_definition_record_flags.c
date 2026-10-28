#include "../../../src/task_tree_core.h"

struct DefinitionRecordFlags { u32 unknown_00; u16 flags; };
extern const struct DefinitionRecordFlags *GetContinuationRecord(void *);

u32 TestDefinitionRecordFlags(void *record,u16 mask)
{
    mask &= GetContinuationRecord(record)->flags;
    if (mask != 0)
        return 1;
    return 0;
}

__asm__(".global GetContinuationRecord\n"
        ".thumb_set GetContinuationRecord,0x080a880d\n");
