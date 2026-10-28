typedef unsigned char u8;
typedef unsigned short u16;
struct PrimaryInventoryRow { u16 item; u8 quantity; u8 unknown_03; };
struct SaveInventory { u8 preceding_data[0x1940]; struct PrimaryInventoryRow rows[361]; };
typedef char RowSize[sizeof(struct PrimaryInventoryRow)==4?1:-1];
extern struct SaveInventory gMissionRewardInventory;
asm(".global gMissionRewardInventory\n.set gMissionRewardInventory,0x02000000");
u8 GetPrimaryInventoryQuantity(u16 item) __asm__("CoreRegion_000388C8");
/* First matching primary-inventory row controls duplicate reward allocation. */
u8 GetPrimaryInventoryQuantity(u16 item)
{
    u16 index;
    for (index = 0; index <= 360; ++index) {
        if (gMissionRewardInventory.rows[index].item == item)
            return gMissionRewardInventory.rows[index].quantity;
    }
    return 0;
}
