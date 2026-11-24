#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed int s32;
typedef struct {u8 bytes[0x3498];} BattleRecord;
typedef void (*ClearFunction)(void*,u32);
extern ClearFunction ClearBytesCell __asm__("0x0836d4b8");
BattleRecord *AllocateRecord(u32) __asm__("0x08022841");
void FreeRecord(BattleRecord*) __asm__("0x08022855");
void ProcessRecords(BattleRecord*,void*,s32,s32,u32,u32,u32,u32) __asm__("0x080a433d");

/* Non-emitting binding for the original Thumb indirect-call veneer. */
__asm__(".thumb\n.global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");
