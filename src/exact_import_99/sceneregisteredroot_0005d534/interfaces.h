#ifndef MISSION_MENU_OPERATION_H
#define MISSION_MENU_OPERATION_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct MissionMenuView {
    u8 unknown0[0x1198];
    u8 parent_mode, state, continuation, secondary_continuation, unknown119c, message;
};
struct MissionKeys { u16 held, pressed; };
extern struct MissionMenuView *gMissionMenu;
extern struct MissionKeys gMissionKeys;
extern u8 gMissionRuntime[];
extern void ResetMissionMenuInput(void);
extern void ConfigureMissionMenuRuntime(void *,u32,u32,u32,u32,u32);
extern void InitializeMissionMenu(struct MissionMenuView *,u32);
extern u32 WaitMissionMenuPanel(void);
extern u32 PollMissionMenuOperation(void);
extern void OpenMissionMenu(u32);
extern u32 ReadMissionSelectionStatus(void);
extern void BeginMissionOperation(u32,u32);
extern u32 InitializeMissionOperation(int);
extern u32 ReadMissionSelectedIndex(void);
extern void CloseMissionMenu(void);
extern void SetMissionMenuMessage(u32);
__asm__(".global gMissionMenu\n.set gMissionMenu,0x0200f448\n.global gMissionKeys\n.set gMissionKeys,0x03000000\n.global gMissionRuntime\n.set gMissionRuntime,0x030008b0\n.global ResetMissionMenuInput\n.thumb_set ResetMissionMenuInput,0x08022b25\n.global ConfigureMissionMenuRuntime\n.thumb_set ConfigureMissionMenuRuntime,0x08029e49\n.global InitializeMissionMenu\n.thumb_set InitializeMissionMenu,0x08061029\n.global WaitMissionMenuPanel\n.thumb_set WaitMissionMenuPanel,0x08011861\n.global PollMissionMenuOperation\n.thumb_set PollMissionMenuOperation,0x0805f4ad\n.global OpenMissionMenu\n.thumb_set OpenMissionMenu,0x0805f44d\n.global ReadMissionSelectionStatus\n.thumb_set ReadMissionSelectionStatus,0x08060dd5\n.global BeginMissionOperation\n.thumb_set BeginMissionOperation,0x0805f4d9\n.global InitializeMissionOperation\n.thumb_set InitializeMissionOperation,0x0805d23d\n.global ReadMissionSelectedIndex\n.thumb_set ReadMissionSelectedIndex,0x08060dc5\n.global CloseMissionMenu\n.thumb_set CloseMissionMenu,0x08013365\n.global SetMissionMenuMessage\n.thumb_set SetMissionMenuMessage,0x080610f9");
#endif
