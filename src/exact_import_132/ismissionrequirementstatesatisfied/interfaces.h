#ifndef MISSION_REQUIREMENT_INTERFACES_H
#define MISSION_REQUIREMENT_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Saved item records are four bytes; only identity participates in this gate. */
typedef struct { u8 item_id; u8 flags; u16 reference; } RequirementItem;
typedef struct { u8 before_items[0x2b08]; RequirementItem items[64]; } RequirementItemSave;
typedef struct __attribute__((packed)) { u8 count; u8 unknown; } RequirementProgress;
typedef struct { u8 before_progress[0x21b4]; RequirementProgress progress[0]; } RequirementProgressSave;
extern RequirementItemSave gRequirementItems;
extern RequirementProgressSave gRequirementProgress;
extern u32 ReadMissionRequirementProperty(u32 mission, u32 property);
typedef char item_stride_is_four[(sizeof(RequirementItem) == 4) ? 1 : -1];
typedef char progress_stride_is_two[(sizeof(RequirementProgress) == 2) ? 1 : -1];
asm(".global gRequirementItems\n.set gRequirementItems,0x02000000\n"
    ".global gRequirementProgress\n.set gRequirementProgress,0x02000000\n"
    ".global ReadMissionRequirementProperty\n.thumb_set ReadMissionRequirementProperty,0x080ce4dd\n");
#endif
