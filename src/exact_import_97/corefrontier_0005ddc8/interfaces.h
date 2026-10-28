typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionStatusRecord { u8 record_id, flags; u16 mission_id; };
struct SelectedMission { u8 unknown00[4]; u8 assignments[2]; u8 unknown06[10]; };
struct MissionSelectionContext {
    u8 unknown00[0x11aa]; u8 status_count; u8 unknown11ab[0x9d];
    /* Physical extent to selected_mission; no runtime count bound is inferred. */
    struct MissionStatusRecord *status_records[130];
    struct SelectedMission *selected_mission;
};
typedef char StatusRecordSize[sizeof(struct MissionStatusRecord)==4?1:-1];
typedef char SelectedMissionSize[sizeof(struct SelectedMission)==16?1:-1];
typedef char StatusRecordsOffset[(u32)&((struct MissionSelectionContext*)0)->status_records==0x1248?1:-1];
typedef char SelectedMissionOffset[(u32)&((struct MissionSelectionContext*)0)->selected_mission==0x1450?1:-1];
extern struct MissionSelectionContext *gMissionSelectionContext;
__asm__(".global gMissionSelectionContext\n.set gMissionSelectionContext,0x0200f448");
