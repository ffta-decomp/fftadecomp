typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
/* Read-only view of the packed ID; remaining record fields are not modeled. */
struct MissionRecord { u16 identifier:10; u16 remaining_bits:6; } __attribute__((packed));
typedef char PackedIdView[(sizeof(struct MissionRecord)==2)?1:-1];
struct MissionCollectionState {
    u8 unknown00[36];
    struct MissionRecord *cached[16];
    u8 snapshot100;
    u8 snapshot101;
    u8 unknown102[70];
    u8 collected_count;
};
struct MissionCollectionRoot { u32 unknown00; struct MissionCollectionState *state; };
typedef char CachedOffset[((u32)&((struct MissionCollectionState *)0)->cached==36)?1:-1];
typedef char SnapshotOffset[((u32)&((struct MissionCollectionState *)0)->snapshot100==100)?1:-1];
typedef char CountOffset[((u32)&((struct MissionCollectionState *)0)->collected_count==172)?1:-1];
extern struct MissionCollectionRoot *MissionCollectionRoot;
__asm__(".global MissionCollectionRoot\n.set MissionCollectionRoot,0x03002810");
u32 MissionSnapshotsDiffer(void);
void ReloadMissionSnapshotFromSave(void);
u32 CollectUpdatedMissionRecords(struct MissionRecord **output,u32 limit,u32 refresh);
s32 StoreCachedMissionRecord(struct MissionRecord *record);
__asm__(".global MissionSnapshotsDiffer\n.thumb_set MissionSnapshotsDiffer,0x08035fc5");
__asm__(".global ReloadMissionSnapshotFromSave\n.thumb_set ReloadMissionSnapshotFromSave,0x08035f8d");
__asm__(".global CollectUpdatedMissionRecords\n.thumb_set CollectUpdatedMissionRecords,0x080d1c95");
__asm__(".global StoreCachedMissionRecord\n.thumb_set StoreCachedMissionRecord,0x080301b1");
