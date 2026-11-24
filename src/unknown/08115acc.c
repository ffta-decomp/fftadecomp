typedef unsigned char u8;
typedef unsigned int u32;
extern void *ResolveAuthoredNestedRecord(void *) __asm__("0x080dd47c");
extern void SetAuthoredRecordCollectionFlag(u8,u8,void *,u32) __asm__("0x080dbed4");
void RemainingBand43_00115ACC(void *record)
{
 ResolveAuthoredNestedRecord(record);
 SetAuthoredRecordCollectionFlag(0,1,0,0);
}
