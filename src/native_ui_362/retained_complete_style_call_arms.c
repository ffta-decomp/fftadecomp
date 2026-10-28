typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *NativeAlternateTextRoot;
extern void ClearNativeTextSpan(void *,u16) asm("RetailCall_08013a88");
extern u32 ProcessNativeTextSpan(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
void ClearAndDrawNativeTextSpan(void *,const u8 *,u32,u32) asm("CoreGlobal36_00089AAC");
void ClearAndDrawNativeTextSpan(void *output,const u8 *text,u32 length,u32 style)
{
    ClearNativeTextSpan(output,(u16)(length<<1));
    if (style == 0) {
        ProcessNativeTextSpan(NativeAlternateTextRoot+1676,(u32)output,text,0,1);
    } else {
        ProcessNativeTextSpan(NativeAlternateTextRoot+1676,(u32)output,text,1,1);
    }
}
__asm__(".global NativeAlternateTextRoot\n.set NativeAlternateTextRoot,0x03002818\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n");
