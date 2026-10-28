/* Observed ROM 0x00064e54, Thumb 0x08064e55, span 40 bytes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SaveImage {
    u8 unused[0x3c28];
    u16 active_mission_id;
} SaveImage;

extern volatile const SaveImage gSaveData;
extern u32 GetMissionProperty(u16 mission_id, u8 selector);

/* True when selector 18 of the currently active mission has observed value 2. */
u8 IsActiveMissionProperty18Two(void)
{
    return GetMissionProperty(gSaveData.active_mission_id, 18) == 2;
}
