#ifndef MISSION_ITEM_RESERVATION_H
#define MISSION_ITEM_RESERVATION_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionItemReservation { u8 item_identity; u8 unknown1; u16 mission_link; };
extern struct MissionItemReservation gMissionItemReservations[64];
typedef char reservation_stride[sizeof(struct MissionItemReservation)==4?1:-1];
typedef char reservation_link_offset[(unsigned long)&((struct MissionItemReservation*)0)->mission_link==2?1:-1];
__asm__(".global gMissionItemReservations\n.set gMissionItemReservations,0x02002b08");
#endif
