typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NestedUnitValueContext {
    u8 unknown_prefix[2];
    u16 script_pc;
    const u8 *script;
};
struct __attribute__((packed)) NestedUnitValueCommand {
    u8 opcode;
    u8 unit_selector;
    u8 expected_unit_value;
    u8 skip_low;
    u8 skip_high;
};
struct CurrentScriptUnit {
    u8 *unit;
};
typedef char UnitValuePcOffset[((u32)&((struct NestedUnitValueContext *)0)->script_pc == 2) ? 1 : -1];
typedef char UnitValueCommandSize[(sizeof(struct NestedUnitValueCommand) == 5) ? 1 : -1];
extern u8 *ResolveScriptUnit(u8 selector);
extern struct CurrentScriptUnit *GetContentContextPointerAt4(void);
__asm__(".global ResolveScriptUnit\n.thumb_set ResolveScriptUnit,0x08125579\n.global GetContentContextPointerAt4\n.thumb_set GetContentContextPointerAt4,0x08096d89");
