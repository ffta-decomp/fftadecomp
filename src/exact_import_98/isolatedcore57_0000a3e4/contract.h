#include "unit_status_flag_view.h"
typedef unsigned int u32;
typedef struct { u16 header; u16 pc_bits; const u8 *script; } ScriptContext;
typedef struct { u8 opcode; u8 unit_id; u8 distance_low; u8 distance_high; } ConditionalUnitSkip;
typedef char ContextPcOffset[((u32)&((ScriptContext *)0)->pc_bits==2)?1:-1];
typedef char ContextScriptOffset[((u32)&((ScriptContext *)0)->script==4)?1:-1];
typedef char CommandSize[(sizeof(ConditionalUnitSkip)==4)?1:-1];
extern u8 *FindUnitPoolRecordById(u32);
extern int UnitField27HasBit13(const UnitStatusFlagView *);
extern int UnitField27HasBit15(const UnitStatusFlagView *);
__asm__(".thumb_set FindUnitPoolRecordById, 0x080c83cd");
__asm__(".thumb_set UnitField27HasBit13, 0x080c8261");
__asm__(".thumb_set UnitField27HasBit15, 0x080c8241");
