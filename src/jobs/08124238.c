/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
struct UnitRecord { void *unit; };
extern const void *GetSceneActionContextBase(void);
extern int CountBattleUnitRecords(const void *context, struct UnitRecord **records);
extern u8 UnitField27HasBit15(const void *unit);
extern u8 UnitField27HasBit14(const void *unit);

asm(".global GetSceneActionContextBase\n.thumb_set GetSceneActionContextBase,0x08096d7d\n.global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9");
struct UnitRecord *FindSceneUnitByStatusPriority(void)
{
    struct UnitRecord *records[13];
    struct UnitRecord *record;
    int count = CountBattleUnitRecords(GetSceneActionContextBase(), records);
    int index;
    for (index = 0; index < count; index++) {
        record = records[index];
        if (UnitField27HasBit15(record->unit) && UnitField27HasBit14(record->unit))
            return record;
    }
    for (index = 0; index < count; index++) {
        record = records[index];
        if (UnitField27HasBit15(record->unit))
            return record;
    }
    return 0;
}
