typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The owner of this record is not yet established. */
#define SELECTED_TEXT_RECORD (*(const u8 *volatile *)0x020020d0)

extern u16 WriteNumericPrefix(u8 *output, u8 value);
extern u16 WriteUnsignedNumberText(u8 *output, u8 value);

#define DEFINE_RECORD_NUMBER_CALLBACK(name, offset) \
u32 name(u8 *output) \
{ \
    const u8 *record = SELECTED_TEXT_RECORD; \
    u8 *number_output = output; \
    if (record[offset] <= 9) \
        number_output += (u16)WriteNumericPrefix(number_output, 8); \
    WriteUnsignedNumberText(number_output, record[offset]); \
    return 0; \
}

#if defined(RECORD_BYTE_20)
DEFINE_RECORD_NUMBER_CALLBACK(WriteRecordByte20AsNumber, 20)
#elif defined(RECORD_BYTE_22)
DEFINE_RECORD_NUMBER_CALLBACK(WriteRecordByte22AsNumber, 22)
#elif defined(RECORD_BYTE_23)
DEFINE_RECORD_NUMBER_CALLBACK(WriteRecordByte23AsNumber, 23)
#elif defined(RECORD_BYTE_24)
DEFINE_RECORD_NUMBER_CALLBACK(WriteRecordByte24AsNumber, 24)
#elif defined(RECORD_BYTE_25)
DEFINE_RECORD_NUMBER_CALLBACK(WriteRecordByte25AsNumber, 25)
#endif
