typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
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

/* Coordinates use raw halfword storage and a signed Y comparison as observed.
 * Sentinel byte roles and the broader indicator policy remain unresolved. */
void ResetBattlePositionTowardUpperEdge(struct BattlePositionRecord *record)
    __asm__("CoreFrontier_000A8F60");
void ResetBattlePositionTowardUpperEdge(struct BattlePositionRecord *record)
{
    u32 was_active;
    record->field_000 = 255;
    record->field_001 = -1;
    record->field_002 = -1;
    was_active = record->flags & 1;
    if (was_active == 0 || (s16)record->current_y > 127) {
        record->target_x = 192;
        record->target_y = 128;
        if (was_active != 0) {
            record->flags = 1;
        } else {
            record->flags = 1;
            record->current_x = 192;
            record->current_y = 160;
        }
    } else {
        record->previous_target_x = record->target_x;
        record->previous_target_y = record->target_y;
        record->target_x = 192;
        record->target_y = (u16)-32;
        record->flags = 7;
    }
}
