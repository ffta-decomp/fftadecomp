typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionIdentity {
    u16 mission_id : 10;
    u16 unknown_bits : 6;
} __attribute__((packed));
struct MissionDefinition {
    u8 unknown_prefix[65];
    u16 restriction_flags;
    u8 unknown_tail[3];
} __attribute__((packed));
typedef char MissionIdentitySize[(sizeof(struct MissionIdentity) == 2) ? 1 : -1];
typedef char MissionDefinitionSize[(sizeof(struct MissionDefinition) == 70) ? 1 : -1];
typedef char MissionRestrictionOffset[((u32)&((struct MissionDefinition*)0)->restriction_flags == 65) ? 1 : -1];
extern const struct MissionDefinition gMissionDefinitions[];
__asm__(".global gMissionDefinitions\n.set gMissionDefinitions,0x0855ae4c");
