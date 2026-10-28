typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeDialogResource { u8 opaque00[16]; u8 *pixel_base; };
/* Same984B actual native context cleared here and consumed by18624. */
struct NativeDialogWindow {
    struct NativeDialogResource *resource;
    u32 auxiliary;
    u8 state_08,width,x,y;
    u16 setting;
    u8 flags_0e,opaque0f,count_10;
    u8 opaque11[703];
    const u8 *text_bank;
    u8 *pixel_buffer;
    u8 encoded_text[128];
    u8 scratch[128];
};
typedef char NativeDialogWindowSize[(sizeof(struct NativeDialogWindow)==984)?1:-1];
extern struct NativeDialogWindow *gNativeDialogWindow;
extern u32 gNativeClearRoutine;
extern void DispatchNativeClear(void*,u32,u32);
__asm__(".global gNativeDialogWindow\n.set gNativeDialogWindow,0x02009190\n"
        ".global gNativeClearRoutine\n.set gNativeClearRoutine,0x0836d4b8\n"
        ".global DispatchNativeClear\n.thumb_set DispatchNativeClear,0x0814224d");
void InitializeNativeDialogContext(struct NativeDialogWindow*,const u8*,struct NativeDialogResource*,u32,u16) __asm__("CoreFrontier_000185C8");
void InitializeNativeDialogContext(struct NativeDialogWindow *context,const u8 *text_bank,
                                  struct NativeDialogResource *resource,u32 auxiliary,u16 tile)
{
    struct NativeDialogWindow *current;
    u32 *clear_routine_cell;
    gNativeDialogWindow=context;
    /* Actual pointer-cell address is defined before the size constant;
     * its loaded callback is consumed inR2 by the retained dispatch veneer. */
    clear_routine_cell=&gNativeClearRoutine;
    asm("" : "+r"(clear_routine_cell));
    DispatchNativeClear(context,984,*clear_routine_cell);
    /* The actual clear callback may replace the published current context. */
    current=gNativeDialogWindow;
    current->resource=resource;
    current->auxiliary=auxiliary;
    current->setting=tile;
    current->text_bank=text_bank;
    current->pixel_buffer=resource->pixel_base+((u32)tile<<5);
}
