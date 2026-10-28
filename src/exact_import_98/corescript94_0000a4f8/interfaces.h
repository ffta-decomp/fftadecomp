#ifndef SCRIPT_UNIT_CONDITION_H
#define SCRIPT_UNIT_CONDITION_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ScriptContext { u16 unknown0, pc; const u8 *script; };
struct ConditionalCommand { u8 opcode, distance_low, distance_high; };
struct UnitRecord {
    u8 unknown0[4];
    u8 kind;
    u8 unknown5[35];
    u16 status_flags;
    u8 unknown42[222];
};
/* This address-relative view describes only the fields this handler reads. */
struct UnitSelectionView {
    u8 unknown0[168];
    u8 selected;
    u8 unknown169[0xef4 - 169];
    struct UnitRecord units[12];
};
extern struct UnitSelectionView gUnitSelection;
extern int UnitField27HasBit14(const struct UnitRecord *);
extern int UnitField27HasBit8(const struct UnitRecord *);
extern int UnitField27HasBit5(const struct UnitRecord *);
typedef char UnitStride264[sizeof(struct UnitRecord)==264?1:-1];
typedef char UnitBankOffset[((u32)&((struct UnitSelectionView *)0)->units==0xef4)?1:-1];
__asm__(".global gUnitSelection\n.set gUnitSelection,0x020020d0\n.global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9\n.global UnitField27HasBit8\n.thumb_set UnitField27HasBit8,0x080c8365\n.global UnitField27HasBit5\n.thumb_set UnitField27HasBit5,0x080c8349");
#endif
