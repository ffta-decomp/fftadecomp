typedef unsigned short u16;
typedef unsigned int u32;
struct RecordField20;
extern u16 ReadRecordField20(const struct RecordField20 *record);
__asm__(".global ReadRecordField20\n.thumb_set ReadRecordField20,0x08005bad");
u32 IsRecordContinuationGateOpen(const struct RecordField20 *record) __asm__("BattleStateDependency_000E2BDC");
u32 IsRecordContinuationGateOpen(const struct RecordField20 *record)
{
    u16 value = ReadRecordField20(record);
    if (value > 257 || value == 2)
        return 1;
    return 0;
}
