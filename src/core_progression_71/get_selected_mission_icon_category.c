/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectedMissionSave { u8 unknown_0000[0x3c28]; u16 selected_mission; };
extern struct SelectedMissionSave gSaveData;
extern u32 GetMissionProperty(u16 mission_id, u8 selector);


/* Mode 1 intentionally queries ID zero; mode 0 treats it as absent. */
u32 GetSelectedMissionIconCategory(u8 mode)
{
    if (mode == 0) {
        u8 icon_category;
        u16 initial_mission = gSaveData.selected_mission;
        if (initial_mission == 0)
            return 6;
        icon_category = GetMissionProperty(initial_mission, 2);
        icon_category += 15;
        if (GetMissionProperty(gSaveData.selected_mission, 1) == 1)
            icon_category = 6;
        return icon_category;
    }
    if (mode == 1) {
        u8 icon_category;
        icon_category = GetMissionProperty(gSaveData.selected_mission, 2);
        icon_category += 15;
        if (GetMissionProperty(gSaveData.selected_mission, 1) == 1)
            icon_category = 6;
        return icon_category;
    }
    return 6;
}
