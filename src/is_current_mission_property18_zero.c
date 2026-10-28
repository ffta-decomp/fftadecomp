/* Observed ROM 0x00064e2c, Thumb 0x08064e2d, span 40 bytes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Only the active mission field is established in this save-image prefix. */
struct SaveStatePrefix { u8 padding[0x3c28]; u16 active_mission_id; };
extern struct SaveStatePrefix gSaveData;
extern u32 GetMissionProperty(u16 mission_id, u8 selector);

/* Tests whether the active mission takes property-18's zero path. */
u8 IsActiveMissionProperty18Zero(void)
{
    return GetMissionProperty(gSaveData.active_mission_id, 18) == 0;
}
