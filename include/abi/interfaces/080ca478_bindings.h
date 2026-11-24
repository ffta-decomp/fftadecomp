typedef unsigned char u8;
typedef unsigned int u32;
extern u32 GetEquippedStat22(const u8 *unit, u32 include_equipment);
extern u32 GetEquippedStat26(const u8 *unit, u32 include_equipment);
__asm__(".thumb_set GetEquippedStat22, 0x080ca6b5\n"
        ".thumb_set GetEquippedStat26, 0x080ca6fd");
