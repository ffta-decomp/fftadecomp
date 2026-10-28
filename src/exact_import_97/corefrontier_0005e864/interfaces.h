typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct MissionRecord { u32 mission_id:10; u32 metadata:6; u8 unknown02[14]; } __attribute__((packed));
/* Only the leading24 bytes are projected; the full unit object is larger. */
struct MissionUnitPrefix { u8 unknown00[22]; u16 mission_id; };
struct MissionChoiceContext {
    u8 unknown00[0x1199]; u8 phase, unknown119a, followup_state, unknown119c, choice;
    u8 unknown119e[0x4e];
    /* Physical storage to1248, not a runtime unit-count bound. */
    struct MissionUnitPrefix *unit_slots[23];
    u8 unknown1248[0x208]; struct MissionRecord *selected_mission;
    struct MissionUnitPrefix *participant;
};
typedef char MissionRecordSize[sizeof(struct MissionRecord)==16?1:-1];
typedef char UnitMissionOffset[(u32)&((struct MissionUnitPrefix*)0)->mission_id==22?1:-1];
typedef char UnitSlotsOffset[(u32)&((struct MissionChoiceContext*)0)->unit_slots==0x11ec?1:-1];
typedef char SelectedMissionOffset[(u32)&((struct MissionChoiceContext*)0)->selected_mission==0x1450?1:-1];
typedef char ParticipantOffset[(u32)&((struct MissionChoiceContext*)0)->participant==0x1454?1:-1];
extern struct MissionChoiceContext *gMissionChoiceContext;
extern u8 ReadMissionSelectorResult(void);
extern s16 ReadMissionSelectedIndex(void);
/* Existing ASM consumes low8 of the caller's full mode register. */
extern u32 QueryMissionChoice(u32);
__asm__(".global gMissionChoiceContext\n.set gMissionChoiceContext,0x0200f448");
__asm__(".global ReadMissionSelectorResult\n.thumb_set ReadMissionSelectorResult,0x08060dd5");
__asm__(".global ReadMissionSelectedIndex\n.thumb_set ReadMissionSelectedIndex,0x08060dc5");
__asm__(".global QueryMissionChoice\n.thumb_set QueryMissionChoice,0x0805d1c1");
