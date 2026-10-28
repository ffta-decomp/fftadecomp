/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct UnitRecord { void *unit; u8 gap[124]; void *context; };
struct QueryContext { struct UnitRecord *record; u32 first; u32 second; u8 result; u8 mode; u8 reserved[2]; };
extern const u32 gClearMemory;
extern void CallR2Trampoline(void *destination, u32 size, u32 routine);
extern u8 UnitField27HasBit15(const void *unit);
extern void QueryCallback(void *record, struct QueryContext *query);
extern void IterateFirst(void *context, void (*callback)(void *, struct QueryContext *), struct QueryContext *query);
extern void IterateSecond(void *context, void (*callback)(void *, struct QueryContext *), struct QueryContext *query);

asm(".global QueryCallback\n.thumb_set QueryCallback,0x080a95ed\n.global IterateFirst\n.thumb_set IterateFirst,0x08099879\n.global IterateSecond\n.thumb_set IterateSecond,0x0809985d");
u8 QueryUnitRecordTraversalRule(struct UnitRecord *record, u32 first, u32 second, u8 mode)
{
    struct QueryContext query;
    CallR2Trampoline(&query, 16, gClearMemory);
    query.record = record;
    query.first = first;
    query.mode = mode;
    query.second = second;
    query.result = 0;
    if (UnitField27HasBit15(record->unit))
        IterateFirst(record->context, QueryCallback, &query);
    else
        IterateSecond(record->context, QueryCallback, &query);
    return query.result;
}
