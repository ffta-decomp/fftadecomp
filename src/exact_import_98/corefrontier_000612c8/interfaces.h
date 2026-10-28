typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MissionInventoryRecord {
    u8 item_id;
    u8 reservation_flags;
    u16 mission_id;
};
typedef char MissionInventoryRecordSize[(sizeof(struct MissionInventoryRecord) == 4) ? 1 : -1];
typedef char MissionInventoryBindingOffset[((u32)&((struct MissionInventoryRecord*)0)->mission_id == 2) ? 1 : -1];
extern struct MissionInventoryRecord gMissionInventory[64];
extern void (*const gMissionInventoryClear)(u8 *, s32);
__asm__(".global gMissionInventory\n.set gMissionInventory,0x02002b08\n.global gMissionInventoryClear\n.set gMissionInventoryClear,0x0836d4b8\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
