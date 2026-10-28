typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct MissionEntry {
    u8 mission_id_low;
    u8 mission_id_high_and_flags;
};

struct MissionEntryOwner {
    u8 unknown_00[0x424];
    struct MissionEntry *entries[1];
};

extern u32 ReadMissionProperty(u16 mission_id, u8 property);
extern u32 MapMissionCategory(u8 category);

u8 ReadEntryMissionCategory(struct MissionEntryOwner **owner, u32 slot_index)
{
    struct MissionEntryOwner *entry_owner = *owner;
    struct MissionEntry *entry = entry_owner->entries[slot_index];
    u8 id_low = entry->mission_id_low;
    u8 id_high = entry->mission_id_high_and_flags;
    u8 id_mask = 3;
    u32 property = ReadMissionProperty(
        ((id_high & id_mask) << 8) | id_low, 2);
    /* Original arithmetic adds in the high byte, then extracts that lane. */
    u32 category_lane = property << 24;
    u8 category;
    category_lane += 0x0f000000u;
    category = category_lane >> 24;

    /* The property helper may update the entry; decode its ID again. */
    id_low = entry->mission_id_low;
    id_high = entry->mission_id_high_and_flags;
    if (ReadMissionProperty(((id_high & id_mask) << 8) | id_low, 1) == 1)
        category = 6;
    return (u8)MapMissionCategory(category);
}

asm(".global ReadMissionProperty\n.thumb_set ReadMissionProperty,0x080ce4dd\n"
    ".global MapMissionCategory\n.thumb_set MapMissionCategory,0x080cb9cd\n");
