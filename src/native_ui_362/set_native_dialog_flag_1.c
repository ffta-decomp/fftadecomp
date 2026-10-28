typedef unsigned char u8;
/* Observed prefix only; full984B extent is proven by185C8. */
struct NativeDialogFlags { u8 opaque00[14]; u8 flags; };
extern struct NativeDialogFlags *gNativeDialogWindow;
__asm__(".global gNativeDialogWindow\n.set gNativeDialogWindow,0x02009190");
void SetNativeDialogFlag1(void) __asm__("CoreFrontier_00018AA8");
void SetNativeDialogFlag1(void)
{
    gNativeDialogWindow->flags|=1;
}
