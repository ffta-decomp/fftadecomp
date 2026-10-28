struct NestedRecord;
struct RecordWithNestedPointer { struct NestedRecord *nested; };
extern struct RecordWithNestedPointer *GetRecordIdentity(void *record);
__asm__(".global GetRecordIdentity\n.thumb_set GetRecordIdentity, 0x080a880d");
struct NestedRecord *GetRecordNestedPointer(void *record) __asm__("sub_080DD47C");
struct NestedRecord *GetRecordNestedPointer(void *record)
{
    return GetRecordIdentity(record)->nested;
}
