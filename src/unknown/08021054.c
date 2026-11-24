typedef unsigned short u16;
typedef unsigned int u32;
extern const u16 gBattleHalfwordLookup[];
u16 ReadBattleLookupHalfword(u32 index)
{
    /* Preserve ARM32 index/address wrapping without inventing a table bound. */
    u32 table_address = (u32)gBattleHalfwordLookup;
    u32 byte_offset = index << 1;
    return *(const u16 *)(table_address + byte_offset);
}
asm(".global gBattleHalfwordLookup\n.set gBattleHalfwordLookup,0x08391224\n");
