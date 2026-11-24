typedef unsigned char u8;typedef unsigned short u16;
struct NestedScript {u16 unknown,pc;};
struct MissionData {u8 prefix[0x219e];u16 active_mission;};
extern struct MissionData gMissionData;
asm(".global gMissionData\n.set gMissionData,0x02000000");
