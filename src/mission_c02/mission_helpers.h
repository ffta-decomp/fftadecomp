#ifndef FFTA_MISSION_C02_HELPERS_H
#define FFTA_MISSION_C02_HELPERS_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void CallR2Trampoline(void *destination, u32 length, u32 callback);
extern void InitializeBattleUnitRecord(void *destination, const void *source,
                                      u32 length, u32 callback);
extern u32 C02_GetCE8A8(void);
extern u32 C02_GetCED2C(void);
extern u32 C02_ExpiredStateZero(void *payload);
extern void C02_ExpiredStateFollowup(void *payload, u32 value);
extern u32 Routine_08002804(void);
extern s32 SignedModulo(s32 dividend, s32 divisor);
extern u32 GetGameFlag(u16 flag);
extern void SetGameFlag(u16 flag, u16 value);
extern u32 ResolveSceneSelectorByte(u8 index);

#define CLEAR_CALLBACK_WORD (*(volatile const u32 *)0x0836d4b8U)
#define COPY_CALLBACK_WORD (*(volatile const u32 *)0x0836d4bcU)

#endif
