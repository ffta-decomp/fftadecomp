typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 ReadCurrentContentIndex(void);
#define CONTENT_RECORDS ((const u8 *)0x0854cd54)

u8 IsCurrentContentRecordByte21Nonzero(void)
{
    u16 record_index = ReadCurrentContentIndex();
    u32 record_offset = (u32)record_index * 40;
    const u8 *record_base = CONTENT_RECORDS;

    /* Keep the byte-field offset separate from the record-table address. */
    __asm__ volatile ("" : "+r" (record_base));
    return record_base[record_offset + 33] != 0;
}
