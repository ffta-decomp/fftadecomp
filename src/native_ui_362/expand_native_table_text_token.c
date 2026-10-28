typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const u8 * const NativeReferenceTextTable[];
extern u32 CopyNativeEncodedText(u8 *,const u8 *) asm("RetailCall_08018C24");
u16 ExpandNativeReferenceTextToken(u8 *,u8) asm("CoreFrontier_0001624C");
u16 ExpandNativeReferenceTextToken(u8 *destination, u8 selector)
{
    return CopyNativeEncodedText(destination, NativeReferenceTextTable[selector]);
}
__asm__(".global NativeReferenceTextTable\n.set NativeReferenceTextTable,0x085516D0\n"
        ".global RetailCall_08018C24\n.thumb_set RetailCall_08018C24,0x08018C25");
