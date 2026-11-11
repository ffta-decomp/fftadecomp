typedef unsigned char u8;
typedef unsigned int u32;
typedef struct RangeRecord {
    u8 prefix[36];
    struct RangeRecord *previous, *next;
} RangeRecord;
typedef struct { void *pool; RangeRecord *head; } RangeRecords;
extern RangeRecord *PrepareRangeRemoval(RangeRecord *);
extern void FreeRangeRecord(void *, RangeRecord *);
asm(".thumb_set PrepareRangeRemoval, 0x08148739\n"
    ".thumb_set FreeRangeRecord, 0x08007171\n");
void CoreFrontier_00148498(RangeRecord *input)
{
    RangeRecord *record;
    RangeRecord *previous, *next;
    RangeRecords *records;
    record = PrepareRangeRemoval(input);
    if (!record)
        return;
    previous = record->previous;
    next = record->next;
    if (previous) {
        previous->next = next;
        next->previous = previous;
        records = (RangeRecords *)0x03003C60;
    } else {
        records = (RangeRecords *)0x03003C60;
        records->head = next;
        next->previous = previous;
    }
    FreeRangeRecord(records->pool, record);
}
