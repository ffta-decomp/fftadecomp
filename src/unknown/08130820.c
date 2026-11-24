typedef unsigned char u8;
typedef unsigned int u32;
struct UnitFormulaView { u8 unknown00_to04[5]; u8 definition_selector; };
struct BattleFormulaRow { u8 unknown00_to32[51]; u8 scale; };
typedef char RowSize[(sizeof(struct BattleFormulaRow)==52)?1:-1];
typedef char ScaleOffset[((u32)&(((struct BattleFormulaRow*)0)->scale)==51)?1:-1];
typedef char SelectorOffset[((u32)&(((struct UnitFormulaView*)0)->definition_selector)==5)?1:-1];
extern const struct BattleFormulaRow gJobDefinitions[];
u32 ReadUnitInnateFormulaScale(const struct UnitFormulaView *unit)
    asm("CoreDependency29_00130820");
u32 ReadUnitInnateFormulaScale(const struct UnitFormulaView *unit)
{
    u32 byte_offset;
    const struct BattleFormulaRow *row;
    byte_offset = sizeof(struct BattleFormulaRow) * unit->definition_selector;
    row = (const struct BattleFormulaRow *)((const u8 *)gJobDefinitions + byte_offset);
    return row->scale;
}
