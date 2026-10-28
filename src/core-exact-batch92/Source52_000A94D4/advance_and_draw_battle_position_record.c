typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct BattlePositionRecord {
    u8 field_000;
    s8 field_001;
    s8 field_002;
    u8 unknown_003;
    u16 current_x;
    u16 current_y;
    u16 target_x;
    u16 target_y;
    u16 previous_target_x;
    u16 previous_target_y;
    u8 flags;
};
extern void AdvanceBattlePositionRecord(struct BattlePositionRecord *, s32, s32);
extern void AppendTransformedSpritesToOamBank48(const u8 *, u32, u32, u32,
                                               u32, u32, u32, u32,
                                               u32, u32, u32);
__asm__(".global AdvanceBattlePositionRecord\n.thumb_set AdvanceBattlePositionRecord, 0x080a901d\n"
        ".global AppendTransformedSpritesToOamBank48\n.thumb_set AppendTransformedSpritesToOamBank48, 0x08001cf1");

void AdvanceAndDrawBattlePositionRecord(void) __asm__("Source52_000A94D4");
void AdvanceAndDrawBattlePositionRecord(void)
{
    register struct BattlePositionRecord *record __asm__("r5") =
        (struct BattlePositionRecord *)0x0200ffc8;
    register const s8 *coordinate_source __asm__("r0");
    s32 source_x;
    s32 source_y;
    /* Retain the native record literal and R5 lifetime across real services. */
    __asm__("" : "+r"(record));
    coordinate_source = (const s8 *)0x0200f3b8;
    /* Keep the two byte reads on the original base before R0 becomes record. */
    __asm__("" : "+r"(coordinate_source));
    source_x = coordinate_source[0];
    source_y = coordinate_source[4];
    AdvanceBattlePositionRecord(record, source_x, source_y);
    /* The real advance can change flags and coordinates; read them afterward. */
    if ((record->flags & 1) != 0) {
        register u32 priority_offset __asm__("r4") = record->unknown_003;
        register const u8 *sprite_list __asm__("r0") = (const u8 *)0x0839454c;
        /* Preserve priority capture before the native sprite-list formation.
         * Every operand is defined; empty constraints emit no instructions. */
        __asm__("" : "+r"(sprite_list) : "r"(priority_offset));
        AppendTransformedSpritesToOamBank48(sprite_list,
                                            (s16)record->current_x,
                                            (s16)record->current_y,
                                            0, 0, 0, 0, 0, 0,
                                            priority_offset, 0);
    }
}
