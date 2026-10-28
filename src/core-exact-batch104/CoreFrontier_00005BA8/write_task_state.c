typedef unsigned short u16;
struct RecordField20 { unsigned char unknown[20]; u16 field20; };
void WriteRecordField20(struct RecordField20 *record, u16 value) __asm__("CoreFrontier_00005BA8");
void WriteRecordField20(struct RecordField20 *record, u16 value)
{
    record->field20 = value;
}
