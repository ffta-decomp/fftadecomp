struct Unit;
struct NestedRecord { struct Unit *unit; };
struct Unit *GetNestedRecordUnit(struct NestedRecord *record)
    __asm__("RemainingBand43_000DD478");
struct Unit *GetNestedRecordUnit(struct NestedRecord *record)
{
    return record->unit;
}
