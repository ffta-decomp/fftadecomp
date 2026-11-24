typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*HandleRoutine)(void *,u32,u32,u32,u32,u32);
struct Record { u8 unknown0[84]; void *primary; void *secondary; };
extern HandleRoutine const gHandleRoutine;
extern void *AllocateWorkspace(u32);
extern void FreeWorkspace(void *);
extern u32 CollectRecords(u8,struct Record **,u32);
void RemainingBand43_000DD808(u8 selector,u8 mode,u8 include_secondary,struct Record *exclude,u32 parameter)
{
    struct Record **records=AllocateWorkspace(96);
    u8 count=CollectRecords(selector,records,parameter);
    u8 index;
    for(index=0;index<count;index++) {
        void *primary,*secondary;
        if(exclude && records[index]==exclude)continue;
        primary=records[index]->primary;
        secondary=records[index]->secondary;
        if(primary)gHandleRoutine(primary,mode,0,0,0,0);
        if(include_secondary && secondary)gHandleRoutine(secondary,mode,0,0,0,0);
    }
    FreeWorkspace(records);
}
asm(".global AllocateWorkspace\n.thumb_set AllocateWorkspace,0x0800a655\n.global FreeWorkspace\n.thumb_set FreeWorkspace,0x0800a669\n.global CollectRecords\n.thumb_set CollectRecords,0x080dcd09\n.global gHandleRoutine\n.set gHandleRoutine,0x08394034\n.global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n");
