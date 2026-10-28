/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct InventoryCountView { u16 item_id; u8 count; u8 unknown03; };
extern struct InventoryCountView *RetailCall_080cb210(u16,s32 *);
asm(".global RetailCall_080cb210\n.thumb_set RetailCall_080cb210,0x080cb211");

u32 HasNonzeroExtensionInventoryCount(void)
{
    s32 count;
    struct InventoryCountView *records=RetailCall_080cb210(362,&count);
    u16 index;
    for (index=0;index<count;index++) {
        if (records[index].count != 0)
            return 1;
    }
    return 0;
}
