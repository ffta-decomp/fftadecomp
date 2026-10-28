typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

/* Only observed storage positions are named; semantic captions are tentative. */
typedef struct SceneProgressView {
    u8 lower_flags : 5;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 upper_flag : 1;
    u8 unknown_01[5];
    u16 field_06;
    u16 field_08;
    u16 unknown_0a;
    u16 field_0c;
    u16 unknown_0e;
    u8 field_10;
} SceneProgressView;

typedef struct SceneProgressContext {
    u8 *records;
    SceneProgressView *view;
    u8 unknown_008[0x674];
    const u8 *configuration_67c;
    const u8 *configuration_680;
} SceneProgressContext;
extern SceneProgressContext *gSceneProgress;
extern u8 gSceneProgressData[];
extern const u8 gSceneConfiguration67c[];
extern const u8 gSceneConfiguration680[];
extern void InitializeSceneSlot(u32 slot, u32 selector, u32 enabled);
extern void SelectInitialProgressRegion(void);
extern void ResetRegionRecords(void);
extern void ClearMissionWorkingRecords(void);
extern void ResetMissionRecordMode(void);
extern void RefreshProgressionState(void);
__asm__(".global gSceneProgress\n.set gSceneProgress,0x03002810\n"
        ".global gSceneProgressData\n.set gSceneProgressData,0x02002c10\n"
        ".global gSceneConfiguration67c\n.set gSceneConfiguration67c,0x08391e40\n"
        ".global gSceneConfiguration680\n.set gSceneConfiguration680,0x083931b0\n"
        ".global InitializeSceneSlot\n.thumb_set InitializeSceneSlot,0x08030045\n"
        ".global SelectInitialProgressRegion\n.thumb_set SelectInitialProgressRegion,0x08043f65\n"
        ".global ResetRegionRecords\n.thumb_set ResetRegionRecords,0x08043f91\n"
        ".global ClearMissionWorkingRecords\n.thumb_set ClearMissionWorkingRecords,0x080d2e25\n"
        ".global ResetMissionRecordMode\n.thumb_set ResetMissionRecordMode,0x080d2e61\n"
        ".global RefreshProgressionState\n.thumb_set RefreshProgressionState,0x08035e05\n");
