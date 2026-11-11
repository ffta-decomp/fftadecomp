typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {u32 unknown0;void *reference;} PendingRecord;
extern void SetRecordControl(void*,u32);
static inline u8 HasReference(PendingRecord *record)
{
 u32 present=(u32)record->reference;
 if(present)present=1;
 return present;
}
void SetPendingRecordControl(PendingRecord *record,u8 control)
{
 if(HasReference(record))SetRecordControl(record->reference,control);
}
__asm__(".global SetRecordControl\n.thumb_set SetRecordControl,0x0809d8d1\n");
