typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gNativeDialogContext;
extern u32 UpdateNativeDialogControl(void *) asm("RetailCall_08017180");
u32 UpdateNativeDialogResourceClose(void) asm("Buffer55_00018A90");
u32 UpdateNativeDialogResourceClose(void)
{
    return (u8)UpdateNativeDialogControl(gNativeDialogContext+20);
}
__asm__(".global gNativeDialogContext\n.set gNativeDialogContext,0x02009190\n"
        ".global RetailCall_08017180\n.thumb_set RetailCall_08017180,0x08017181\n");
