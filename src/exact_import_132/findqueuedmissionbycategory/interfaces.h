typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Observed packed fields only; all other bits retain neutral names. */
struct MissionDescriptor {
    u16 mission_id:10;
    u16 unknown_10:6;
    u8 unknown_16:2;
    u8 category:3;
    u8 unknown_21:3;
} __attribute__((packed));
struct MissionNode {
    struct MissionDescriptor *descriptor;
    struct MissionNode *previous;
    struct MissionNode *next;
};
struct MissionQueueSave {
    u8 unknown_prefix[0x28c8];
    struct MissionNode *queue;
};
extern struct MissionQueueSave gMissionQueueSave;
extern int IsMissionRequirementStateSatisfied(u16);
__asm__(".global gMissionQueueSave\n.set gMissionQueueSave,0x02000000");
__asm__(".global IsMissionRequirementStateSatisfied\n.thumb_set IsMissionRequirementStateSatisfied,0x080ceecd");
