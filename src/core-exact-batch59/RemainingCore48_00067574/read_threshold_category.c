typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct WordStrideEntry {
    u16 identifier;
    u16 unknown_02;
};
struct ThresholdEntryOwner {
    u8 unknown_00[0x424];
    struct WordStrideEntry entries[1];
};
typedef char ThresholdEntryStrideMustBeFour[sizeof(struct WordStrideEntry) == 4 ? 1 : -1];
extern u32 ReadItemCategory(u16 item_id);

u32 ReadThresholdEntryCategory(struct ThresholdEntryOwner **owner, u32 slot)
{
    u8 *entry_address = (u8 *)*owner;
    u16 identifier;
    u32 item_id;
    slot <<= 2;
    entry_address += sizeof(((struct ThresholdEntryOwner *)0)->unknown_00);
    entry_address += slot;
    identifier = *(u16 *)entry_address;
    item_id = 394;
    if (identifier <= 85)
        --item_id;
    return (u8)ReadItemCategory(item_id) + 13;
}

asm(".global ReadItemCategory\n.thumb_set ReadItemCategory,0x080cb99d\n");
