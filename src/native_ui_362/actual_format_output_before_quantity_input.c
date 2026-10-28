typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u16 NativeQuantityTextScratch[];
extern u8 NativeQuantityTextSurface[];
extern u8 *NativeQuantityTextRoot;
extern const u8 *const NativeQuantityLabels[];
extern const u8 *CreateNativeQuantityWindow(u32,u8 *,u32,u32,u16,const u8 *,s32,s32,u8) asm("RetailCall_08037a30");
extern u32 FormatNativeQuantityText(u8 *,u16,u32) asm("RetailCall_080142dc");
extern u32 ResolveNativeQuantityTextPosition(u32,u32,u32,u32) asm("RetailCall_0808b92c");
extern u32 RenderNativeQuantityText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern u32 MeasureNativeQuantityText(const u8 *) asm("RetailCall_080161bc");
void RenderNativeResourceQuantityMessage(u32,u32,const u8 *,s32) asm("CoreRegion_0003E1C0");
void RenderNativeResourceQuantityMessage(u32 resource_id,u32 quantity,const u8 *incoming_message,s32 kind)
{
    register const u8 *message asm("r9")=incoming_message;
    u16 id=resource_id;
    u32 count=(u8)quantity;
    u8 *initial_surface=NativeQuantityTextSurface;
    register u32 position asm("r1");
    asm("" : "+r"(message));
    CreateNativeQuantityWindow(5,initial_surface,0,0,id,0,kind,2,1);
    if (count>1) {
        u16 *digits=NativeQuantityTextScratch;
        register u8 *format_output asm("r0");
        s32 skipped;
        register u8 *surface asm("r8");
        u32 width;
        format_output=(u8 *)digits;
        asm("" : "+r"(format_output));
        FormatNativeQuantityText(format_output,(u16)count,2);
        skipped=0;
        while (skipped<5 && digits[skipped]==0x1881)
            ++skipped;
        digits += skipped;
        surface=NativeQuantityTextSurface;
        asm("" : "+r"(surface));
        position=ResolveNativeQuantityTextPosition(5,(u32)surface,0,2);
        asm("" : "+r"(position));
        RenderNativeQuantityText(NativeQuantityTextRoot+3148,position,(const u8 *)digits,1,1);
        width=(u16)MeasureNativeQuantityText((const u8 *)digits);
        position=ResolveNativeQuantityTextPosition(5,(u32)surface,width,2);
        asm("" : "+r"(position));
        RenderNativeQuantityText(NativeQuantityTextRoot+3148,position,NativeQuantityLabels[17],1,1);
        position=ResolveNativeQuantityTextPosition(5,(u32)surface,4,2);
        asm("" : "+r"(position));
        RenderNativeQuantityText(NativeQuantityTextRoot+3148,position,message,1,1);
    } else {
        position=ResolveNativeQuantityTextPosition(5,(u32)initial_surface,0,2);
        asm("" : "+r"(position));
        RenderNativeQuantityText(NativeQuantityTextRoot+3148,position,message,1,1);
    }
}
__asm__(".global NativeQuantityTextScratch\n.set NativeQuantityTextScratch,0x02003cb0\n"
        ".global NativeQuantityTextSurface\n.set NativeQuantityTextSurface,0x0600afe0\n"
        ".global NativeQuantityTextRoot\n.set NativeQuantityTextRoot,0x03002810\n"
        ".global NativeQuantityLabels\n.set NativeQuantityLabels,0x085668b0\n"
        ".global RetailCall_08037a30\n.thumb_set RetailCall_08037a30,0x08037a31\n"
        ".global RetailCall_080142dc\n.thumb_set RetailCall_080142dc,0x080142dd\n"
        ".global RetailCall_0808b92c\n.thumb_set RetailCall_0808b92c,0x0808b92d\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_080161bc\n.thumb_set RetailCall_080161bc,0x080161bd\n");
