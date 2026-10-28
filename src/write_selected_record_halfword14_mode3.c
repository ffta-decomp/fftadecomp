typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 fields_00_0d[14];
    volatile u16 field_0e;
} TextRecordContext;

#define TEXT_RECORD_CONTEXT ((volatile TextRecordContext *)0x020020d0)

extern void WriteHalfwordTextWithMode(u8 *output, u16 value, u32 mode);

u32 WriteSelectedRecordHalfword14WithMode3(u8 *output)
{
    u16 value = TEXT_RECORD_CONTEXT->field_0e;

    WriteHalfwordTextWithMode(output, value, 3);
    return 0;
}
