typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MissionReservationRecord {
    u8 item_id;
    u8 reservation_flags;
    u16 mission_id;
};
/* Leading fields only; this view does not establish the complete mission size. */
struct MissionReservationPrefix {
    u8 unknown_prefix[4];
    u8 reserved_items[2];
};
struct MissionReservationContext {
    u8 unknown_prefix[0x11aa];
    u8 reservation_base;
    u8 unknown_11ab[0x1248 - 0x11ab];
    struct MissionReservationRecord *items[64];
    u8 unknown_1348[0x1450 - 0x1348];
    struct MissionReservationPrefix *mission;
};
typedef char ReservationRecordSize[(sizeof(struct MissionReservationRecord) == 4) ? 1 : -1];
typedef char ReservationBaseOffset[((u32)&((struct MissionReservationContext*)0)->reservation_base == 0x11aa) ? 1 : -1];
typedef char ReservationItemsOffset[((u32)&((struct MissionReservationContext*)0)->items == 0x1248) ? 1 : -1];
typedef char ReservationMissionOffset[((u32)&((struct MissionReservationContext*)0)->mission == 0x1450) ? 1 : -1];
extern struct MissionReservationContext *gMissionReservations;
extern void (*const gMissionReservationClear)(u8 *, s32);
__asm__(".global gMissionReservations\n.set gMissionReservations,0x0200f448\n.global gMissionReservationClear\n.set gMissionReservationClear,0x0836d4b8\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
