typedef unsigned char u8;
typedef unsigned int u32;
struct Record {u8 unknown0[48];u32 flags;};
extern void *AllocateWorkspace(u32);
extern void FreeWorkspace(void *);
extern u32 CollectRecords(u8,struct Record **,u32);
void RemainingBand43_000DBED4(u8 selector,u8 mode,struct Record *exclude,u32 parameter)
{
    struct Record **records=AllocateWorkspace(96);
    u8 count=CollectRecords(selector,records,parameter);
    u8 index;
    for(index=0;index<count;index++) {
        struct Record *record;
        if(exclude && records[index]==exclude)continue;
        record=records[index];
        if(mode)record->flags &= ~1u;
        else record->flags |= 1;
    }
    FreeWorkspace(records);
}
asm(".global AllocateWorkspace\n.thumb_set AllocateWorkspace,0x0800a655\n.global FreeWorkspace\n.thumb_set FreeWorkspace,0x0800a669\n.global CollectRecords\n.thumb_set CollectRecords,0x080dcd09\n");
