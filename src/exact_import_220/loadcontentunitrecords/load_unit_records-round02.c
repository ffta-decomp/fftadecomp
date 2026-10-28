typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct UnitDefinition { u8 fields[48]; } UnitDefinition;
typedef struct LiveUnit {
    u8 before_occupancy[4];
    u8 occupied;
    u8 remaining_fields[259];
} LiveUnit;
typedef struct UnitDefinitionBank {
    u16 count;
    u16 reserved;
    const UnitDefinition *definitions;
} UnitDefinitionBank;
typedef char DefinitionStride[(sizeof(UnitDefinition) == 48) ? 1 : -1];
typedef char UnitStride[(sizeof(LiveUnit) == 264) ? 1 : -1];

extern void ConstructContentUnit(LiveUnit *unit, const UnitDefinition *definition,
                                 u32 mode) __asm__("0x080c9644");

s32 LoadContentUnitRecords(UnitDefinitionBank *bank, LiveUnit *destination,
                           s32 maximum)
{
    s32 limit = maximum;
    LiveUnit *cursor = destination;
    const UnitDefinition *definition = bank->definitions;
    s32 source_index = 0;
    s32 loaded = 0;

    for (; source_index < bank->count && loaded < limit;) {
        /* Physical vacancy search has no independent end bound in retail. */
        while (cursor->occupied)
            cursor++;
        ConstructContentUnit(cursor, definition, 0);
        source_index++;
        definition++;
        loaded++;
        /* Keep this cursor: the next pass observes the constructor's occupancy. */
    }
    return loaded;
}
