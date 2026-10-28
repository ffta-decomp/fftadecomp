typedef unsigned short u16;
struct RecordField20 { unsigned char unknown[20]; u16 field20; };
u16 ReadRecordField20(const struct RecordField20 *record) __asm__("CoreFrontier_00005BAC");
u16 ReadRecordField20(const struct RecordField20 *record)
{
    return record->field20;
}
