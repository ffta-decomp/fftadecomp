typedef unsigned char u8;
typedef unsigned int u32;
extern int CompactSaveRecords64(void) __asm__("RetailCall_080caa74");
/* Compact the64 mission-item records before testing their actual count. */
u32 CompactMissionItemsAndTestNonempty(void) __asm__("RemainingCore48_000680E0");
u32 CompactMissionItemsAndTestNonempty(void)
{
    return (u8)CompactSaveRecords64() != 0;
}
__asm__(".global RetailCall_080caa74\n.thumb_set RetailCall_080caa74,0x080caa75");
