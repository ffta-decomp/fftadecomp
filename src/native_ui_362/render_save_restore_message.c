typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gSaveRestoreContext;
extern u16 gSaveRestoreMessageTiles[];
extern void CopyNativeHalfwords(const void*,void*,u32) asm("RetailCall_0814186C");
extern u32 ProcessNativeEncodedTextStream(void*,u32,const u8*,u32,u32) asm("RetailCall_08015110");
void RenderSaveRestoreMessage(const u8*) asm("Remaining38_00138354");
void RenderSaveRestoreMessage(const u8 *encoded_text)
{
    u16 zero;
    register u16 *zero_source asm("r1")=&zero;
    /* Native defines this actual SP+4 source in R1 before storing zero,
     * then copies it to the first CpuSet argument before reusing R1. */
    asm("" : "+r"(zero_source));
    *zero_source=0;
    CopyNativeHalfwords(zero_source,gSaveRestoreMessageTiles,0x01000320u);
    ProcessNativeEncodedTextStream(gSaveRestoreContext+0xF9C,
        (u32)gSaveRestoreMessageTiles,encoded_text,5,1);
}
__asm__(".global gSaveRestoreContext\n.set gSaveRestoreContext,0x030027d8\n.global gSaveRestoreMessageTiles\n.set gSaveRestoreMessageTiles,0x0600bae0\n.global RetailCall_0814186C\n.thumb_set RetailCall_0814186C,0x0814186d\n.global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111");
