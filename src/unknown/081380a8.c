typedef unsigned int u32;
extern void FillNativeDisplayTilePattern(u32,u32,u32) asm("RetailCall_08138014");
void InitializeSaveRestoreTilePattern(void) asm("Remaining38_001380A8");
void InitializeSaveRestoreTilePattern(void)
{
    FillNativeDisplayTilePattern(0,0,2);
}
__asm__(".global RetailCall_08138014\n.thumb_set RetailCall_08138014,0x08138015");
