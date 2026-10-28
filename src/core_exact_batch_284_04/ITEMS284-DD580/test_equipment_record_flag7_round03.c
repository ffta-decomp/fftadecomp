typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EquipmentRecordFlagPrefix { u8 unknown00[12]; u16 flags; };
u32 TestEquipmentRecordFlag7(const struct EquipmentRecordFlagPrefix *record) __asm__("RemainingBand43_000DD580");
/* Preserve the materialized 0/1 equality gate used by the item-property
 * category consumer, without naming the unknown flag's game meaning. */
u32 TestEquipmentRecordFlag7(const struct EquipmentRecordFlagPrefix *record)
{
    u32 shifted_flags = record->flags >> 7;
    register u32 mask asm("r1") = 1;
    u32 result;
    /* Both actual predicate inputs are defined before the separate result=0
     * phase. The empty input-only annotation emits no instruction or value. */
    asm("" : : "r"(shifted_flags), "r"(mask));
    result = 0;
    switch (shifted_flags & mask) {
    case 1:
        result = 1;
        break;
    }
    return result;
}
