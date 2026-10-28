#ifndef MISSION_PROGRESSION_26_H
#define MISSION_PROGRESSION_26_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

struct MissionQueueLink {
    u8 *record;
    struct MissionQueueLink *previous;
    struct MissionQueueLink *next;
};

#define MISSION_DEFINITIONS ((const u8 *)0x0855ae4c)
#define MISSION_QUEUE_HEAD (*(struct MissionQueueLink **)0x020028c8)
#define MISSION_QUEUE_LINKS ((struct MissionQueueLink *)0x020025c8)
#define PROGRESSION_RECORDS ((u8 *)0x02002cb4)
#define PROGRESSION_DEFINITIONS ((const u8 *)0x085653f0)

typedef void (*MissionClearBytes)(void *destination, u32 size);
#define MISSION_CLEAR (*(MissionClearBytes const *)0x0836d4b8)

extern u32 GetGameFlag(u16 flag);
extern void SetGameFlag(u16 flag, u16 value);
extern u8 ReadSaveByte(u16 index);
extern void WriteSaveByte(u16 index, u8 value);
extern void ApplyMissionProgressSlot(u32 index) __asm__("IP03_ApplyMissionProgress");
extern u32 GetSceneSelectorValueByIndex(u32 index);
extern u32 NextRandom15(void);
extern s32 SignedModulo(s32 value, s32 divisor);
/* Symbol-only declarations: direct calls to retained, source-verified entries. */
extern void PopulateEligibleMissionQueue(u32 refresh) __asm__("0x080cfcd0");
extern u32 MissionQueueEventAllowed(u8 mode) __asm__("0x0800a5d4");

/* Entry identities stay fixed while the C names describe observed policy. */
void ApplyMissionRecordCommands(u8 *record) __asm__("CoreDependency29_000D0F74");
u32 SelectPendingMissionEvent(u8 *output_status) __asm__("CoreDependency29_000D1A18");
void UpdateMissionProgressionSlot(u32 index) __asm__("CoreDependency29_000CFA48");

#endif
