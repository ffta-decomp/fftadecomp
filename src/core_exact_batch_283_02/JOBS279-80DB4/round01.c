typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__asm__(
    ".global JobChangeUpdateDerivedBytes\n"
    ".thumb_set JobChangeUpdateDerivedBytes, 0x080ca2e9\n"
    ".global JobChangeReadEquipmentValue16\n"
    ".thumb_set JobChangeReadEquipmentValue16, 0x080ca395\n"
    ".global JobChangeRefreshDerivedByte\n"
    ".thumb_set JobChangeRefreshDerivedByte, 0x080ca611\n"
    ".global JobChangeReadCombinedEquipmentValue\n"
    ".thumb_set JobChangeReadCombinedEquipmentValue, 0x080ca5c5\n"
);

extern void JobChangeUpdateDerivedBytes(u8 *unit);
extern u32 JobChangeReadEquipmentValue16(const u8 *unit);
extern u32 JobChangeRefreshDerivedByte(u8 *unit);
extern u32 JobChangeReadCombinedEquipmentValue(const u8 *unit);

void CoreScene34_00080DB4(u8 *unit)
{
    JobChangeUpdateDerivedBytes(unit);

    *(volatile u16 *)(*(u8 * volatile *)0x03002818U + 0x1CF2) =
        (u16)JobChangeReadEquipmentValue16(unit);

    *(volatile u16 *)(*(u8 * volatile *)0x03002818U + 0x1CF4) =
        (u16)JobChangeRefreshDerivedByte(unit);

    *(volatile u16 *)(*(u8 * volatile *)0x03002818U + 0x1CF6) =
        (u16)JobChangeReadCombinedEquipmentValue(unit);
}
