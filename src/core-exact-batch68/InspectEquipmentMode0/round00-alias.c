typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 InspectEquipment(void *unit, u16 replacement_item, u8 slot, u8 mode) __asm__("InspectEquipmentForScan");
/* Mode zero asks the equipment trial policy to check the complete set. */
u32 InspectEquipmentMode0(void *unit, u32 replacement_item, u32 slot)
{
    return (u8)InspectEquipment(unit, (u16)replacement_item, (u8)slot, 0);
}
