typedef unsigned char u8;
typedef unsigned int u32;

extern u32 ReadEquippedStat20(const u8 *unit, u32 include_equipment);
extern u32 ReadEquippedStat24(const u8 *unit, u32 include_equipment);
asm(".global ReadEquippedStat20\n.thumb_set ReadEquippedStat20, 0x080ca625\n.global ReadEquippedStat24\n.thumb_set ReadEquippedStat24, 0x080ca66d");
