typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MissionRecord {
    u32 mission_id:10; u32 id_metadata:6;
    u32 unknown16:2; u32 status:3; u32 unknown21:3;
    u8 remaining_ticks; u8 unknown04[12];
} __attribute__((packed));
struct MissionDefinition { u8 unknown00[64]; u8 retention_ticks; u8 unknown41[5]; } __attribute__((packed));
struct MissionNode { struct MissionRecord *record; struct MissionNode *previous,*next; };
struct MissionRuntime { u8 unknown00[0x28c8]; struct MissionNode *head; };
typedef char MissionRecordSize[sizeof(struct MissionRecord)==16?1:-1];
typedef char MissionDefinitionSize[sizeof(struct MissionDefinition)==70?1:-1];
typedef char MissionNodeSize[sizeof(struct MissionNode)==12?1:-1];
extern const struct MissionDefinition gRetentionMissionDefinitions[];
extern struct MissionNode gRetentionMissionNodes[64];
extern struct MissionRuntime gRetentionMissionRuntime;
extern void (*const gRetentionMissionClear)(void*,u32);
/* Caller passes a full register; existing ASM consumes low8 of mode. */
extern void DetachMissionAssignments(struct MissionRecord*,u32);
__asm__(".global gRetentionMissionDefinitions\n.set gRetentionMissionDefinitions,0x0855ae4c");
__asm__(".global gRetentionMissionNodes\n.set gRetentionMissionNodes,0x020025c8");
__asm__(".global gRetentionMissionRuntime\n.set gRetentionMissionRuntime,0x02000000");
__asm__(".global gRetentionMissionClear\n.set gRetentionMissionClear,0x0836d4b8");
__asm__(".global DetachMissionAssignments\n.thumb_set DetachMissionAssignments,0x080cf119");
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
