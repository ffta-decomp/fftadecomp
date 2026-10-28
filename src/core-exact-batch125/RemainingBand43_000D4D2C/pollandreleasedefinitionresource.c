#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern u32 IsDefinitionResourceStateOne(const void *);
extern void UnlinkDefinitionResource(void *);
extern void ReleaseDefinitionResourceGroup(u8);
void *PollAndReleaseDefinitionResource(void *handle, u8 group)
{
    if (handle != 0 && IsDefinitionResourceStateOne(handle) != 0) {
        UnlinkDefinitionResource(handle);
        ReleaseDefinitionResourceGroup(group);
        return 0;
    }
    return handle;
}

asm(".global IsDefinitionResourceStateOne\n.thumb_set IsDefinitionResourceStateOne,0x800c149\n"
    ".global UnlinkDefinitionResource\n.thumb_set UnlinkDefinitionResource,0x800c225\n"
    ".global ReleaseDefinitionResourceGroup\n.thumb_set ReleaseDefinitionResourceGroup,0x800c1c9\n");
