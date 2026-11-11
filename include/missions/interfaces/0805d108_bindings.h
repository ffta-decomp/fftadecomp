#ifndef MISSION_RESULT_SET_H
#define MISSION_RESULT_SET_H
typedef unsigned char u8;
typedef unsigned short u16;
struct MissionResultSetView { u8 unknown0[0x145c]; u16 entries[16]; };
extern struct MissionResultSetView *gMissionResultSet;
__asm__(".global gMissionResultSet\n.set gMissionResultSet,0x0200f448");
#endif
