#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

/* Both header fields use the native unaligned little-endian halfword view. */
struct __attribute__((packed)) DefinitionResourceHeader {
    u16 flags;
    u16 relative_offset;
};
typedef char DefinitionResourceHeaderMustBe4Bytes[
    sizeof(struct DefinitionResourceHeader) == 4 ? 1 : -1];

extern void *CreateDefinitionResourceVariantOne(u8,const void *,const void *,u32,u32);
extern void *CreateDefinitionResourceVariantZero(u8,const void *,const void *,u32,u32);
extern void SetDefinitionResourceOption(void *,u32);
extern void SetDefinitionResourceValue(void *,s16);
extern void SetDefinitionResourceFlagBits(void *,u8,u8);
void *CreateDefinitionResource(u8 slot, const struct DefinitionResourceHeader *record,
                                u16 value, u8 option)
{
    const u8 *data = (const u8 *)record + 4;
    const u8 *relative_data = (const u8 *)record + record->relative_offset;
    void *handle;
    u16 attributes;
    u32 flag14_control;
    if (record->flags & 1)
        handle = CreateDefinitionResourceVariantOne(slot,data,relative_data,0,0);
    else
        handle = CreateDefinitionResourceVariantZero(slot,data,relative_data,0,0);
    SetDefinitionResourceOption(handle,option);
    SetDefinitionResourceValue(handle,(s16)value);
    /* Reload packed flags after the real backend calls. */
    attributes = record->flags;
    /* Header mask4 controls the resource flag at bit14. */
    flag14_control = 4;
    flag14_control &= attributes;
    SetDefinitionResourceFlagBits(handle,(u8)flag14_control,(u8)(attributes & 8));
    return handle;
}

asm(".global CreateDefinitionResourceVariantOne\n.thumb_set CreateDefinitionResourceVariantOne,0x800b2a5\n"
    ".global CreateDefinitionResourceVariantZero\n.thumb_set CreateDefinitionResourceVariantZero,0x800b395\n"
    ".global SetDefinitionResourceOption\n.thumb_set SetDefinitionResourceOption,0x800bedd\n"
    ".global SetDefinitionResourceValue\n.thumb_set SetDefinitionResourceValue,0x800bed9\n"
    ".global SetDefinitionResourceFlagBits\n.thumb_set SetDefinitionResourceFlagBits,0x800bf05\n");
