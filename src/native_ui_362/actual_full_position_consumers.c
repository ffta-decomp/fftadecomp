typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u16 NativeAmountTextScratch[];
extern u8 NativeAmountTextSurface[];
extern u8 *NativeAmountTextRoot;
extern const u8 *const NativeAmountTextCatalog[];
extern u32 FormatNativeAmountText(u8 *,u16,u32) asm("RetailCall_080142dc");
extern u32 ResolveNativeAmountTextPosition(u32,u32,u32,u32) asm("RetailCall_0808b92c");
extern u32 RenderNativeAmountText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern u32 MeasureNativeAmountText(const u8 *) asm("RetailCall_080161bc");
void RenderNativeInventoryAmountMessage(u32,const u8 *) asm("CoreRegion_0003E2E0");
void RenderNativeInventoryAmountMessage(u32 amount,const u8 *incoming_message)
{
    register const u8 *message asm("r9")=incoming_message;
    u16 *digits=NativeAmountTextScratch;
    s32 skipped;
    register u8 *surface asm("r8");
    register u32 position asm("r1");
    u32 width;
    asm("" : "+r"(message));
    FormatNativeAmountText((u8 *)digits,(u16)amount,5);
    skipped=0;
    while (skipped<5 && digits[skipped]==0x1881)
        ++skipped;
    digits += skipped;
    surface=NativeAmountTextSurface;
    asm("" : "+r"(surface));
    position=ResolveNativeAmountTextPosition(5,(u32)surface,0,0);
    asm("" : "+r"(position));
    RenderNativeAmountText(NativeAmountTextRoot+3148,position,(const u8 *)digits,1,1);
    width=(u16)MeasureNativeAmountText((const u8 *)digits);
    position=ResolveNativeAmountTextPosition(5,(u32)surface,width,0);
    asm("" : "+r"(position));
    RenderNativeAmountText(NativeAmountTextRoot+3148,position,NativeAmountTextCatalog[732],1,1);
    position=ResolveNativeAmountTextPosition(5,(u32)surface,0,2);
    asm("" : "+r"(position));
    RenderNativeAmountText(NativeAmountTextRoot+3148,position,message,1,1);
}
__asm__(".global NativeAmountTextScratch\n.set NativeAmountTextScratch,0x02003cb0\n"
        ".global NativeAmountTextSurface\n.set NativeAmountTextSurface,0x0600afe0\n"
        ".global NativeAmountTextRoot\n.set NativeAmountTextRoot,0x03002810\n"
        ".global NativeAmountTextCatalog\n.set NativeAmountTextCatalog,0x085567f0\n"
        ".global RetailCall_080142dc\n.thumb_set RetailCall_080142dc,0x080142dd\n"
        ".global RetailCall_0808b92c\n.thumb_set RetailCall_0808b92c,0x0808b92d\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_080161bc\n.thumb_set RetailCall_080161bc,0x080161bd\n");
