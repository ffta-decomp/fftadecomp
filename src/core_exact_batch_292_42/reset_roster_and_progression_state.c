#ifndef ROSTER_PROGRESSION_RESET_INTERFACES_H
#define ROSTER_PROGRESSION_RESET_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitRecord;
extern u8 gProgressionResetSave[];
extern void ClearFlaggedRosterStatuses(void);
extern void UpdateRosterProgressFlags(void);
extern void WriteSaveByte(u16 index,u8 value);
extern void SetGameFlag(u16 flag,u16 value);
extern void ResetUnitBattleFields(struct UnitRecord *,int count);
extern void ResetSerialTimerIrq(void);
extern void QueuePersistentContentRequest(u16 identifier);
extern void CopySaveHalfword2194To2192AndSetFlag21F(void);
__asm__(
".global gProgressionResetSave\n.set gProgressionResetSave,0x02000000\n"
".global ClearFlaggedRosterStatuses\n.thumb_set ClearFlaggedRosterStatuses,0x0802D935\n"
".global UpdateRosterProgressFlags\n.thumb_set UpdateRosterProgressFlags,0x0802D825\n"
".global WriteSaveByte\n.thumb_set WriteSaveByte,0x080C95C1\n"
".global SetGameFlag\n.thumb_set SetGameFlag,0x080C9575\n"
".global ResetUnitBattleFields\n.thumb_set ResetUnitBattleFields,0x0809A951\n"
".global ResetSerialTimerIrq\n.thumb_set ResetSerialTimerIrq,0x08004C41\n"
".global QueuePersistentContentRequest\n.thumb_set QueuePersistentContentRequest,0x08009AFD\n"
".global CopySaveHalfword2194To2192AndSetFlag21F\n.thumb_set CopySaveHalfword2194To2192AndSetFlag21F,0x08009FD1\n");
#endif


/* The numeric save-field and request labels remain neutral. Each initialized
 * address/constant below is consumed by an original store; the empty operands
 * retain their observed definition stages without adding instructions. */
void ResetRosterAndProgressionState(void)
{
    register u32 save_address asm("r4") = (u32)gProgressionResetSave;
    register u32 address asm("r0");
    register u32 first_phase asm("r1");
    register u32 byte_phase asm("r2");
    register u32 halfword_offset asm("r3");
    asm("" : "+r"(save_address));

    first_phase = 0x3C24;
    asm("" : "+r"(first_phase));
    address = save_address + first_phase;
    asm("" : "+r"(address));
    first_phase = 0;
    asm("" : "+r"(first_phase));
    *(u32 *)address = first_phase;

    byte_phase = 0x219E;
    asm("" : "+r"(byte_phase));
    address = save_address + byte_phase;
    asm("" : "+r"(address));
    byte_phase = 0;
    asm("" : "+r"(byte_phase));
    *(u16 *)address = first_phase;

    halfword_offset = 0x3C28;
    asm("" : "+r"(halfword_offset));
    address = save_address + halfword_offset;
    asm("" : "+r"(address));
    *(u16 *)address = first_phase;

    first_phase = 0x3C2A;
    asm("" : "+r"(first_phase));
    address = save_address + first_phase;
    asm("" : "+r"(address));
    *(u8 *)address = byte_phase;

    ClearFlaggedRosterStatuses();
    UpdateRosterProgressFlags();
    WriteSaveByte(13,0);
    WriteSaveByte(8,0);
    SetGameFlag(64,0);
    save_address += 0x80;
    asm("" : "+r"(save_address));
    ResetUnitBattleFields((struct UnitRecord *)save_address,24);
    ResetSerialTimerIrq();
    QueuePersistentContentRequest(167);
    CopySaveHalfword2194To2192AndSetFlag21F();
}
