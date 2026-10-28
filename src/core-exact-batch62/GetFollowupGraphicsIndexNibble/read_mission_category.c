typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct __attribute__((packed)) MissionCategoryRow {
    u8 packed_nibbles;
    u8 unknown_01;
};
struct MissionCategoryTable {
    u8 unknown_prefix[4];
    struct MissionCategoryRow rows[1];
};
typedef char MissionCategoryRowMustBeTwoBytes[sizeof(struct MissionCategoryRow) == 2 ? 1 : -1];
extern const struct MissionCategoryTable gMissionCategoryTable;

u32 GetFollowupGraphicsIndexNibble(u16 entry_id)
{
    const u8 *table_bytes = (const u8 *)&gMissionCategoryTable;
    u32 byte_offset = (u32)entry_id * sizeof(struct MissionCategoryRow);
    byte_offset += sizeof(gMissionCategoryTable.unknown_prefix);
    return table_bytes[byte_offset] >> 4;
}

asm(".global gMissionCategoryTable\n.set gMissionCategoryTable,0x083d3d14\n");
