typedef unsigned char u8;
typedef unsigned int u32;
struct Record;
extern void *GetRecordNestedPointer(void *record);
extern void SetCollectedRecordFlag(u8 selector, u8 mode,
                                   struct Record *exclude, u32 parameter);
void ClearRelatedRecordFlags(void *record) __asm__("RemainingBand43_000EDB80");
void ClearRelatedRecordFlags(void *record)
{
    u32 parameter = (u32)GetRecordNestedPointer(record);
    SetCollectedRecordFlag(5, 1, 0, parameter);
}
__asm__(".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer,0x080DD47D\n"
        ".global SetCollectedRecordFlag\n.thumb_set SetCollectedRecordFlag,0x080DBED5\n");
