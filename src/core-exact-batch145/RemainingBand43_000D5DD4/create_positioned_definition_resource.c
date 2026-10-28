#include "../../../src/task_tree_core.h"
typedef signed short s16;
struct __attribute__((packed)) DefinitionResourceHeader {
    u16 flags;
    u16 relative_offset;
};
typedef char HeaderSize[sizeof(struct DefinitionResourceHeader)==4?1:-1];
extern void *CreateKindTwoDefinition(const void *,const void *,u16,u8,int,int,int,int,u32,u32);
extern void SetDefinitionOption(void *,u32);
void *CreatePositionedDefinitionResource(const struct DefinitionResourceHeader *record,
    u16 id,u16 x,u16 y,u16 group,u8 palette,u8 option)
{
    const u8 *data = (const u8 *)record + 4;
    const u8 *relative_data = (const u8 *)record + record->relative_offset;
    register u32 flags asm("r3") = 0;
    u32 attributes;
    u32 first_flag;
    register u32 flag_constant asm("r1");
    void *object;
    /* Preserve the initialized numeric flag value before the two mask arms;
     * this constraint emits no instruction or memory effect. */
    asm("" : "+r" (flags));
    attributes = record->flags;
    flag_constant = 4;
    asm("" : "+r" (flag_constant));
    first_flag = attributes;
    first_flag &= flag_constant;
    if (first_flag != 0)
        flags = 0x2000;
    if (attributes & 8) {
        register u32 merge asm("r0");
        flag_constant = 0x4000;
        asm("" : "+r" (flag_constant));
        merge = flag_constant;
        asm("" : : "r" (merge));
        flags |= merge;
    }
    object = CreateKindTwoDefinition(data,relative_data,id,1,
        (s16)x,(s16)y,0,(s16)group,palette,flags);
    SetDefinitionOption(object,option);
    return object;
}
asm(".global CreateKindTwoDefinition\n.thumb_set CreateKindTwoDefinition,0x08011349\n"
    ".global SetDefinitionOption\n.thumb_set SetDefinitionOption,0x08011139\n");
