#include "../../../src/task_tree_core.h"

struct DefinitionRecordFlags {
    u8 unknown_00[48];
    u32 flags;
};
extern void *DefinitionRecordIdentity(void *);
u32 ReadDefinitionRecordFlag20(void *) asm("RemainingBand43_000DF8B0");
u32 ReadDefinitionRecordFlag20(void *record)
{
    struct DefinitionRecordFlags *identity=DefinitionRecordIdentity(record);
    u32 result;
    if ((identity->flags&32)==0) {
        result=0;
        asm("" : : "r"(result));
    } else {
        result=1;
        asm("" : : "r"(result));
    }
    return result;
}
asm(".global DefinitionRecordIdentity\n.thumb_set DefinitionRecordIdentity,0x080dd351\n");
