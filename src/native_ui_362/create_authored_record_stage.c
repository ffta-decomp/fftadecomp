typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RecordEvent {u16 phase,unknown2;const void *definition;u8 opaque8[12];u16 mode,unknown22;u32 opaque24;};
typedef u32 (*RecordCallback)(void*,struct RecordEvent*,void*);
extern u32 CountAuthoredRecordRows(const void*);
extern void *CreateAuthoredRecordTask(RecordCallback,u16,const struct RecordEvent*,void*);
__asm__(".global CountAuthoredRecordRows\n.thumb_set CountAuthoredRecordRows,0x080dd495\n.global CreateAuthoredRecordTask\n.thumb_set CreateAuthoredRecordTask,0x08005b6d");
typedef char RecordEventMustBe28[(sizeof(struct RecordEvent)==28)?1:-1];
void *RemainingBand43_00115AE4(const void *definition,u32 input_mode,void *parent)
{
    struct RecordEvent event;
    u8 mode=input_mode;
    void *result;
    if((u8)CountAuthoredRecordRows(definition)!=0) {
        event.mode=mode;
        event.definition=definition;
        result=CreateAuthoredRecordTask((RecordCallback)0x0811584d,48,&event,parent);
    } else {
        result=0;
    }
    return result;
}
