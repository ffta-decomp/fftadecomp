typedef unsigned int u32;
struct BattleRecordCapture { u32 count; u32 *cursor; };
/* The output store precedes the count read, as in the original callback. */
u32 AppendBattleUnitRecordAddress(u32 record_address, struct BattleRecordCapture *capture)
{
    u32 *cursor = capture->cursor;
    *cursor++ = record_address;
    capture->count++;
    capture->cursor = cursor;
    return 1;
}
