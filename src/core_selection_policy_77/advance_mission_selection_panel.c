/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct { u16 id:10; u16 unknown_id_bits:6; u8 unknown2[2], assignment4, assignment5; } __attribute__((packed)) Mission;
typedef struct { u8 unknown0[22]; u16 mission_id; } Unit;
typedef struct {
    u8 unknown0[0x1199];
    u8 state, continuation, second_continuation, field119c, message;
    u8 unknown119e[2];
    u8 field11a0, field11a1, unknown11a2[2];
    u16 selection11a4, cursor11a6;
    u8 panel_count, unknown11a9[0x11ec - 0x11a9];
    u32 panel_records[(0x1450 - 0x11ec)/4];
    Mission *mission;
    Unit *unit;
} MissionRoot;
typedef struct { u8 unknown0[16]; u8 mode16, mode17; } MissionContext;
typedef struct { u8 unknown0[0x219e]; u16 last_mission; } MissionSave;
typedef struct {u16 held, pressed;} KeyState;
extern MissionRoot *mission_root;
extern MissionContext mission_context;
extern MissionSave mission_save;
extern KeyState keys;
extern u8 mission_display[];
typedef char root_size_check[sizeof(MissionRoot)==0x1458 ? 1 : -1];
extern u16 PollMessage(void);
asm(".global PollMessage\n.thumb_set PollMessage, 0x08011861");
extern void CloseMessage(void);
asm(".global CloseMessage\n.thumb_set CloseMessage, 0x08013365");
extern s8 GetConfirmation(void);
asm(".global GetConfirmation\n.thumb_set GetConfirmation, 0x08013381");
extern void SetMessageRoot(MissionRoot *);
asm(".global SetMessageRoot\n.thumb_set SetMessageRoot, 0x08013391");
extern void DrawMissionPane(void *, int, void *, s16, s16, u8);
asm(".global DrawMissionPane\n.thumb_set DrawMissionPane, 0x08029e49");
extern void ResetPane(u8, u8, u8, u8);
asm(".global ResetPane\n.thumb_set ResetPane, 0x0802a2c1");
extern void RememberMission(u16);
asm(".global RememberMission\n.thumb_set RememberMission, 0x0805d109");
extern void ForgetMission(u16);
asm(".global ForgetMission\n.thumb_set ForgetMission, 0x0805d13d");
extern u8 AdvanceSelection(void);
asm(".global AdvanceSelection\n.thumb_set AdvanceSelection, 0x0805d4ed");
extern void UpdateSelection(void);
asm(".global UpdateSelection\n.thumb_set UpdateSelection, 0x0805d949");
extern u8 PollSelection(u8,u8,u8);
asm(".global PollSelection\n.thumb_set PollSelection, 0x0805da11");
extern void HandleSelection(u8);
asm(".global HandleSelection\n.thumb_set HandleSelection, 0x0805daa9");
extern u8 SelectContinuation(void);
asm(".global SelectContinuation\n.thumb_set SelectContinuation, 0x0805df95");
extern u8 AdvanceMode5(void);
asm(".global AdvanceMode5\n.thumb_set AdvanceMode5, 0x0805e355");
extern u8 AdvanceMode6(void);
asm(".global AdvanceMode6\n.thumb_set AdvanceMode6, 0x0805e5c1");
extern void InitializeMissionChoice(void);
asm(".global InitializeMissionChoice\n.thumb_set InitializeMissionChoice, 0x0805e799");
extern void AdvanceMissionChoice(void);
asm(".global AdvanceMissionChoice\n.thumb_set AdvanceMissionChoice, 0x0805e865");
extern void AdvanceMissionDetail(void);
asm(".global AdvanceMissionDetail\n.thumb_set AdvanceMissionDetail, 0x0805e925");
extern void AdvanceMissionCommit(void);
asm(".global AdvanceMissionCommit\n.thumb_set AdvanceMissionCommit, 0x0805ea0d");
extern void SetPanelMode(u8);
asm(".global SetPanelMode\n.thumb_set SetPanelMode, 0x0805f44d");
extern u16 PollPanel(void);
asm(".global PollPanel\n.thumb_set PollPanel, 0x0805f4ad");
extern void PopulatePanel(void *,int);
asm(".global PopulatePanel\n.thumb_set PopulatePanel, 0x0805f541");
extern u8 GetPanelMode(void);
asm(".global GetPanelMode\n.thumb_set GetPanelMode, 0x08060de1");
extern void SetPanelRequest(u8,u8);
asm(".global SetPanelRequest\n.thumb_set SetPanelRequest, 0x08060ded");
extern void ShowRootMessage(MissionRoot *,u8);
asm(".global ShowRootMessage\n.thumb_set ShowRootMessage, 0x08061029");
extern void ShowMessage(u8);
asm(".global ShowMessage\n.thumb_set ShowMessage, 0x080610f9");
extern void ShowContextMessage(MissionRoot *,u8);
asm(".global ShowContextMessage\n.thumb_set ShowContextMessage, 0x08061519");
extern void SetGameFlag(u16,u8);
asm(".global SetGameFlag\n.thumb_set SetGameFlag, 0x080c9575");
extern void AssignMission(Mission *,Unit *,u16,u16);
asm(".global AssignMission\n.thumb_set AssignMission, 0x080d0b49");
extern void RemoveMission(Mission *);
asm(".global RemoveMission\n.thumb_set RemoveMission, 0x080d0ed5");
extern Mission * NextSpecialMission(void);
asm(".global NextSpecialMission\n.thumb_set NextSpecialMission, 0x080d2d55");
asm(".global mission_root\n.set mission_root, 0x0200f448");
asm(".global mission_context\n.set mission_context, 0x020020d0");
asm(".global mission_save\n.set mission_save, 0x02000000");
asm(".global keys\n.set keys, 0x03000000");
asm(".global mission_display\n.set mission_display, 0x030008b0");

static inline u16 MissionId(Mission *mission)
{
    return mission->id;
}
u32 AdvanceMissionSelectionPanel(void)
{
    switch (mission_root->state) {
    case 0:
        InitializeMissionChoice();
        mission_root->continuation = 4;
        mission_root->state = 1;
        break;
    case 1:
        if (PollPanel()) mission_root->state = mission_root->continuation;
        break;
    case 2:
        if (PollMessage()) mission_root->state = mission_root->continuation;
        UpdateSelection();
        break;
    case 3: {
        u16 finished = PollMessage();
        PollPanel();
        if (finished) mission_root->state = mission_root->continuation;
        break;
    }
    case 18:
        ShowRootMessage(mission_root, mission_root->message);
        mission_root->continuation = mission_root->second_continuation;
        mission_root->state = 2;
        break;
    case 19:
        ShowContextMessage(mission_root, mission_context.mode16);
        mission_root->continuation = mission_root->second_continuation;
        mission_root->state = 2;
        break;
    case 4:
        if (PollSelection(0, 3, 0)) return AdvanceSelection();
        break;
    case 5:
        HandleSelection(0);
        UpdateSelection();
        break;
    case 6: {
        u8 next = SelectContinuation();
        if (next == 0) mission_root->field11a0 = 1;
        ShowRootMessage(mission_root, mission_root->message);
        mission_root->continuation = next;
        mission_root->state = 2;
        break;
    }
    case 7:
        ResetPane(0,0,0,0);
        SetPanelMode(4);
        PopulatePanel(mission_root->panel_records, mission_root->panel_count);
        mission_root->continuation = 8;
        mission_root->state = 1;
        break;
    case 8:
        AdvanceMissionChoice();
        break;
    case 20:
        CloseMessage();
        if (mission_root->unit) mission_root->unit->mission_id = 0;
        ShowMessage(76);
        mission_root->continuation = 7;
        mission_root->state = 2;
        break;
    case 9:
        AdvanceMissionDetail();
        break;
    case 10: {
        u8 changed = 0;
        switch(GetPanelMode()) {
        case 5: changed = AdvanceMode5(); break;
        case 6: changed = AdvanceMode6(); break;
        }
        if (changed) PollPanel();
        break;
    }
    case 11:
        ResetPane(0,0,0,0);
        SetPanelMode(6);
        SetPanelRequest(6,0);
        mission_root->continuation = 10;
        mission_root->state = 1;
        PollPanel();
        break;
    case 12:
        CloseMessage();
        if (mission_context.mode17 == 4) ShowMessage(86);
        mission_root->second_continuation = 5;
        mission_root->continuation = 19;
        mission_root->state = 2;
        break;
    case 13: {
        u8 choice = GetConfirmation();
        SetMessageRoot(mission_root);
        if ((s8)choice < 0) mission_root->state = 5;
        else if ((s8)choice > 0) {
            CloseMessage();
            mission_root->message = 85;
            mission_root->second_continuation = 15;
            mission_root->continuation = 18;
            mission_root->state = 2;
        } else {
            CloseMessage();
            mission_root->continuation = 14;
            mission_root->state = 2;
        }
        break;
    }
    case 14: {
        MissionRoot *selection = mission_root;
        if (selection->selection11a4 == 0) {
            selection->message = 79;
            mission_root->second_continuation = 17;
            mission_root->state = 18;
        } else {
            selection->cursor11a6 = 0;
            selection->field119c = 0;
            mission_root->message = 78;
            mission_root->second_continuation = 16;
            mission_root->state = 18;
        }
        DrawMissionPane(mission_display,0,0,20,17,1);
        break;
    }
    case 16:
        AdvanceMissionCommit();
        break;
    case 15:
        CloseMessage();
        mission_root->field11a1 = 0;
        mission_root->field11a0 = 1;
        mission_root->continuation = 0;
        mission_root->state = 2;
        break;
    case 17:
        if (keys.pressed & 1) {
            Mission *mission;
            mission_root->field11a1 = 0;
            SetPanelRequest(3,0);
            mission = mission_root->mission;
            AssignMission(mission, mission_root->unit, mission->assignment4, mission->assignment5);
            RememberMission(MissionId(mission_root->mission));
            mission_save.last_mission = mission_root->mission->id;
            if (MissionId(mission_root->mission) == 383) {
                Mission *pending;
                SetGameFlag(54,0);
                while ((pending = NextSpecialMission()) != 0) {
                    ForgetMission(MissionId(pending));
                    RemoveMission(pending);
                }
            }
            mission_root->state = 0;
            return 7;
        }
        break;
    }
    return 4;
}
