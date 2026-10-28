typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct DefinitionEntry {
    u8 unknown_before_06[6];
    u8 selector;
    u8 unknown_at_07;
};
struct NestedRecord;
struct Unit;
extern const struct DefinitionEntry DefinitionEntries[];
extern struct NestedRecord *GetRecordNestedPointer(void *context);
extern struct Unit *GetNestedRecordUnit(struct NestedRecord *record);
extern u8 UnitField03InRange6To18(const struct Unit *unit);
__asm__(".global DefinitionEntries\n.set DefinitionEntries, 0x083947d8\n"
        ".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer, 0x080dd47d\n"
        ".global GetNestedRecordUnit\n.thumb_set GetNestedRecordUnit, 0x080dd479\n"
        ".global UnitField03InRange6To18\n.thumb_set UnitField03InRange6To18, 0x080c8385");

u32 IsDefinitionUnitGateBlocked(void *context, u16 definition_id)
    __asm__("CoreContinuation_000D3B98");
u32 IsDefinitionUnitGateBlocked(void *context, u16 definition_id)
{
    const u8 *base = (const u8 *)DefinitionEntries;
    u32 offset = (u32)definition_id * 8 - 8;
    const struct DefinitionEntry *entry;
    /* Retail keeps the table symbol and scaled-minus-eight offset separate.
     * Both operands are defined; this empty constraint emits no instructions. */
    __asm__("" : "+r" (offset) : "r" (base));
    entry = (const struct DefinitionEntry *)(base + offset);
    if (entry->selector == 16 &&
        !UnitField03InRange6To18(GetNestedRecordUnit(GetRecordNestedPointer(context))))
        return 1;
    return 0;
}
