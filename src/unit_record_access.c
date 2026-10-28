typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unused_prefix[4];
    u16 property04;
    u16 property05;
    /* Packed bytes +8..+10 hold two four-bit slots and two source IDs. */
    u32 slot_a : 4;
    u32 source_a : 8;
    u32 slot_b : 4;
    u32 source_b : 8;
    u8 properties09[3];
} __attribute__((packed)) UnitRecord14;
typedef char UnitRecord14HasFourteenBytes[(sizeof(UnitRecord14) == 14) ? 1 : -1];

typedef struct {
    u8 prefix[4];
    u8 record_index;
} UnitRecordSelector;

extern const UnitRecord14 gUnitRecords14[];
extern u8 gRecordCopyBuffer[];
extern void (*const gCopyRecordMemory)(void *, const void *, u32);
extern u8 UnitHasIndexedRecord(const UnitRecordSelector *unit);
extern u32 GetUnitProperty(const u8 *unit, u8 property);
extern const void *ReadRecordCopySource(u8 source_index);

static inline const UnitRecord14 *RecordForUnit(const UnitRecordSelector *unit)
{
    return &gUnitRecords14[unit->record_index];
}

/* Load the selected 32-byte source when the indexed unit record names one.
 * A missing source still returns the slot; ordinary units delegate to the
 * existing unit-property accessor. */
u8 LoadUnitRecordSlot(const UnitRecordSelector *unit, u8 selector)
{
    if (UnitHasIndexedRecord(unit)) {
        const UnitRecord14 *record = &gUnitRecords14[unit->record_index];
        if (selector == 1) {
            if (record->source_a)
                gCopyRecordMemory(gRecordCopyBuffer + record->slot_a * 32,
                                  ReadRecordCopySource(record->source_a - 1), 32);
            return record->slot_a;
        } else {
            if (record->source_b)
                gCopyRecordMemory(gRecordCopyBuffer + record->slot_b * 32,
                                  ReadRecordCopySource(record->source_b - 1), 32);
            return record->slot_b;
        }
    }
    return GetUnitProperty((const u8 *)unit, selector == 1 ? 6 : 7);
}

u16 ReadUnitRecordProperty04(const UnitRecordSelector *unit)
{
    if (UnitHasIndexedRecord(unit)) return RecordForUnit(unit)->property04;
    return GetUnitProperty((const u8 *)unit, 4);
}

u16 ReadUnitRecordProperty05(const UnitRecordSelector *unit)
{
    if (UnitHasIndexedRecord(unit)) return RecordForUnit(unit)->property05;
    return GetUnitProperty((const u8 *)unit, 5);
}

u8 ReadUnitRecordProperty09(const UnitRecordSelector *unit)
{
    if (UnitHasIndexedRecord(unit)) return RecordForUnit(unit)->properties09[0];
    return GetUnitProperty((const u8 *)unit, 9);
}

u8 ReadUnitRecordProperty10Or11(const UnitRecordSelector *unit, u8 selector)
{
    if (UnitHasIndexedRecord(unit)) {
        const UnitRecord14 *record = RecordForUnit(unit);
        if (selector == 1) return record->properties09[1];
        return record->properties09[2];
    }
    return GetUnitProperty((const u8 *)unit, selector == 1 ? 10 : 11);
}
