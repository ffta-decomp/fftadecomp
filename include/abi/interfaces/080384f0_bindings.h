typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct MissionRecord {u8 type,status;u16 mission;};
struct MissionBankState {u8 unknown00[0x2b08];struct MissionRecord records[64];};
extern struct MissionBankState gMissionBankState;
asm(".global gMissionBankState\n.set gMissionBankState,0x02000000");
typedef char RecordSize[(sizeof(struct MissionRecord)==4)?1:-1];
