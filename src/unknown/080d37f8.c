typedef unsigned char u8;
typedef unsigned int u32;
extern u32 HasManagedTaskPayloadBitZero(void);
extern u32 HasManagedTaskPayloadBitOne(void);
__asm__(".global HasManagedTaskPayloadBitZero\n.thumb_set HasManagedTaskPayloadBitZero, 0x080d3971\n"
        ".global HasManagedTaskPayloadBitOne\n.thumb_set HasManagedTaskPayloadBitOne, 0x080d39b1");

/* Preserve two real queries and their short-circuit order, not one snapshot. */
u32 QueryBothManagedTaskPayloadBits(void)
    __asm__("SceneActionDependency_000D37F8");
u32 QueryBothManagedTaskPayloadBits(void)
{
    if ((u8)HasManagedTaskPayloadBitZero() != 0) {
        if ((u8)HasManagedTaskPayloadBitOne() != 0)
            return 1;
    }
    return 0;
}
