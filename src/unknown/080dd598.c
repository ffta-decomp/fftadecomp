typedef unsigned int u32;
typedef struct {u32 unknown0;u32 reference;} PendingRecord;
u32 HasPendingRecordReference(PendingRecord *record)
{
 u32 present=record->reference;
 if(present)present=1;
 return present;
}
