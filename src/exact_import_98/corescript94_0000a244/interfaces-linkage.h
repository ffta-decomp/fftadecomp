typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NestedUnitBranchContext {
    u8 unknown_prefix[2];
    u16 script_pc;
    const u8 *script;
};
struct NestedUnitBranchCommand {
    u8 opcode;
    u8 unit_selector;
    u8 skip_low;
    u8 skip_high;
};
typedef char NestedBranchPcOffset[((u32)&((struct NestedUnitBranchContext *)0)->script_pc == 2) ? 1 : -1];
typedef char NestedBranchScriptOffset[((u32)&((struct NestedUnitBranchContext *)0)->script == 4) ? 1 : -1];
typedef char NestedUnitBranchCommandSize[(sizeof(struct NestedUnitBranchCommand) == 4) ? 1 : -1];
extern u8 *ResolveScriptUnit(u8 selector);
extern int UnitField27HasBit5(const void *unit);
extern int UnitField27HasBit8(const void *unit);
extern int UnitField27HasBit15(const void *unit);
extern int UnitField27HasBit14(const void *unit);
extern int UnitField19IsZero(const void *unit);
extern u8 UnitStateE8HasBit6(const void *unit);
extern u8 UnitStateE9HasBit0(const void *unit);
extern u8 UnitStateE9HasBit3(const void *unit);
extern u8 UnitStateE9HasBit4(const void *unit);
__asm__(".global ResolveScriptUnit\n.thumb_set ResolveScriptUnit,0x08125579");

__asm__(".global UnitField27HasBit5\n.thumb_set UnitField27HasBit5,0x080c8349\n.global UnitField27HasBit8\n.thumb_set UnitField27HasBit8,0x080c8365\n.global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9");
