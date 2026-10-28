#ifndef MISSION_CANCELLATION_H
#define MISSION_CANCELLATION_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ParticipantView { u8 unknown0[22]; u16 field22; };
struct MissionOperationView {
    u8 unknown0[0x119f];
    u8 selection_flag;
    u8 cancellation_active;
    u8 unknown11a1[8];
    u8 operation_count;
    u8 unknown11aa[2];
    void *operations[16];
    u8 unknown11ec[0x1450-0x11ec];
    void *selected_mission;
    struct ParticipantView *selected_participant;
};
struct SaveSceneView { u8 unknown0[0x1f69]; u8 selector; };
extern struct MissionOperationView *gMissionOperation;
extern struct SaveSceneView gMissionSave;
extern u8 gMissionRuntime[];
extern void ResetSelectedMission(void);
extern u32 ResolveCurrentSceneSelector(u32 selector);
extern u32 EnumerateMissionOperations(void **output,u32 capacity,u32 slot);
extern void ConfigureMissionRuntime(void *,u32,u32,u32,u32,u32);
extern void SetMissionDisplayOptions(u32,u32,u32,u32);
extern void OpenMissionChooser(u32 mode);
extern void SetMissionChooserEntries(void **entries,int count);
typedef char count_offset[(unsigned long)&((struct MissionOperationView *)0)->operation_count==0x11a9?1:-1];
typedef char mission_offset[(unsigned long)&((struct MissionOperationView *)0)->selected_mission==0x1450?1:-1];
__asm__(".global gMissionOperation\n.set gMissionOperation,0x0200f448\n.global gMissionSave\n.set gMissionSave,0x02000000\n.global gMissionRuntime\n.set gMissionRuntime,0x030008b0\n.global ResetSelectedMission\n.thumb_set ResetSelectedMission,0x0805dd65\n.global ResolveCurrentSceneSelector\n.thumb_set ResolveCurrentSceneSelector,0x08036351\n.global EnumerateMissionOperations\n.thumb_set EnumerateMissionOperations,0x080d0591\n.global ConfigureMissionRuntime\n.thumb_set ConfigureMissionRuntime,0x08029e49\n.global SetMissionDisplayOptions\n.thumb_set SetMissionDisplayOptions,0x0802a2c1\n.global OpenMissionChooser\n.thumb_set OpenMissionChooser,0x0805f44d\n.global SetMissionChooserEntries\n.thumb_set SetMissionChooserEntries,0x0805f541");
#endif
