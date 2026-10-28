typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
extern u8 *gNativeDialogWindow;
extern u32 RefreshNativeWindowTargetSize(void*);
extern void TransferNativeWindowRectangle(void*,u32,u32,u32,u32,u32,u32,u32);
__asm__(".global gNativeDialogWindow\n.set gNativeDialogWindow,0x02009190\n"
        ".global RefreshNativeWindowTargetSize\n.thumb_set RefreshNativeWindowTargetSize,0x080172f1\n"
        ".global TransferNativeWindowRectangle\n.thumb_set TransferNativeWindowRectangle,0x080157a9");
u32 RefreshNativeDialogTargetBuffer(void) __asm__("Buffer55_000189A0");
u32 RefreshNativeDialogTargetBuffer(void)
{
    u32 update_status=(u8)RefreshNativeWindowTargetSize(gNativeDialogWindow+20);
    if(update_status) {
        u8 *context=gNativeDialogWindow;
        void *pixels;
        u32 x;
        s32 signed_y;
        u32 y_argument;
        u32 root_address;
        /* Preserve this actual captured root separately from the later reload. */
        asm("" : "+r"(context));
        pixels=*(void **)(*(u8 **)context+20);
        x=(u8)(context[10]+1);
        signed_y=*(s8 *)(context+11);
        /* The signed working source is preserved; each branch defines the
         * independently normalized LOW8 call argument. */
        if(context[14]&2)
            y_argument=(u8)(signed_y+1);
        else
            y_argument=(u8)signed_y;
        /* Native rematerializes the actual pointer-cell address after the
         * coordinate branch, rather than retaining the old address over it. */
        root_address=0x02009190;
        asm("" : "+r"(root_address));
        context=*(u8 **)root_address;
        TransferNativeWindowRectangle(pixels,x,y_argument,context[9],context[16],32,
            *(u16 *)(context+12),11);
    }
    return update_status;
}
