typedef unsigned char u8;
typedef unsigned int u32;
extern u32 *AllocateRecordScratch(u32 bytes);
extern void FreeRecordScratch(void *buffer);
extern void *GetBattleActionRegistry(void);
extern u32 CollectBattleRecords(void *registry,u32 *records);
asm(".global AllocateRecordScratch\n.thumb_set AllocateRecordScratch,0x0800a655\n.global FreeRecordScratch\n.thumb_set FreeRecordScratch,0x0800a669\n.global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n.global CollectBattleRecords\n.thumb_set CollectBattleRecords,0x08099d35\n");
u32 CopyActiveBattleRecords(u32 *output) asm("RemainingBand43_000DD434");
u32 CopyActiveBattleRecords(u32 *output)
{
    u32 *records=AllocateRecordScratch(96);
    u8 count=CollectBattleRecords(GetBattleActionRegistry(),records);
    u8 index=0;
    while(index<count) {
        output[index]=records[index];
        index++;
    }
    FreeRecordScratch(records);
    return count;
}
