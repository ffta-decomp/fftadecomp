typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gNativeDialogContext;
extern u32 UpdateNativeDialogControl(void *) asm("RetailCall_080172f0");
u32 UpdateNativeDialogSimpleClose(void) asm("Buffer55_00018A0C");
u32 UpdateNativeDialogSimpleClose(void)
{
    return (u8)UpdateNativeDialogControl(gNativeDialogContext+20);
}
__asm__(".global gNativeDialogContext\n.set gNativeDialogContext,0x02009190\n"
        ".global RetailCall_080172f0\n.thumb_set RetailCall_080172f0,0x080172f1\n");
