typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MissionInventoryRecord {
    u8 item_id;
    u8 reservation_flags;
    u16 mission_id;
};
struct MissionItemChoiceContext {
    u8 unknown_prefix[0x11aa];
    u8 item_count;
    u8 unknown_11ab[0x1248 - 0x11ab];
    struct MissionInventoryRecord *items[64];
};
typedef char MissionItemRecordSize[(sizeof(struct MissionInventoryRecord) == 4) ? 1 : -1];
typedef char MissionItemCountOffset[((u32)&((struct MissionItemChoiceContext*)0)->item_count == 0x11aa) ? 1 : -1];
typedef char MissionItemListOffset[((u32)&((struct MissionItemChoiceContext*)0)->items == 0x1248) ? 1 : -1];
extern struct MissionItemChoiceContext *gMissionItemChoices;
__asm__(".global gMissionItemChoices\n.set gMissionItemChoices,0x0200f448");
