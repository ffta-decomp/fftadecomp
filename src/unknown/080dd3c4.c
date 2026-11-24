typedef unsigned char u8;
typedef unsigned int u32;
extern u32 CapturePrimaryBattleRecords(u32 *);
extern u32 CaptureSecondaryBattleRecords(u32 *);
asm(".global CapturePrimaryBattleRecords\n.thumb_set CapturePrimaryBattleRecords,0x080dd3f1\n"
    ".global CaptureSecondaryBattleRecords\n.thumb_set CaptureSecondaryBattleRecords,0x080dd435\n");
u32 CollectBattleRegistryRecordAddresses(u32 *output)
    __asm__("RemainingBand43_000DD3C4");
u32 CollectBattleRegistryRecordAddresses(u32 *output)
{
    u8 count;
    register u32 second __asm__("r0");
    count=CapturePrimaryBattleRecords(output);
    output+=count;
    second=(u8)CaptureSecondaryBattleRecords(output);
    /* DD3DC/DE defines a normalized second value in R0 before addition.
     * Retain that initialized value boundary; no emitted instructions. */
    asm("" : "+r" (second));
    count+=second;
    return count;
}
