typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gNativeDetailContext;
extern u8 gNativeMenuGraphics[];
extern u8 gNativeMenuDisplay[];
extern const u8 gNativeCaptionResources[];
extern u8 *ConfigureNativeMenuWindow(u32,u32,void*,void*,void*,void*,void*,void*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void SnapshotNativeWindowRectangle(u32);
extern void DrawNativeTextFrame(u16*,u32,u32,u32,u32,u32,u32,u32);
extern u16 *NativeLayerCell(u32,u32,u32,u32);
extern void WriteNativeTilePairs(u32,u16*,u16,u16,u16);
extern void CopyNativeHalfwords(const void*,void*,u32);
extern u32 ProcessNativeEncodedText(void*,u32,const u8*,u32,u32);
__asm__(".global gNativeDetailContext\n.set gNativeDetailContext,0x03002810\n"
        ".global gNativeMenuGraphics\n.set gNativeMenuGraphics,0x03002740\n"
        ".global gNativeMenuDisplay\n.set gNativeMenuDisplay,0x030009e0\n"
        ".global gNativeCaptionResources\n.set gNativeCaptionResources,0x085668b0\n"
        ".global ConfigureNativeMenuWindow\n.thumb_set ConfigureNativeMenuWindow,0x0808a269\n"
        ".global SnapshotNativeWindowRectangle\n.thumb_set SnapshotNativeWindowRectangle,0x0808aa19\n"
        ".global DrawNativeTextFrame\n.thumb_set DrawNativeTextFrame,0x08016801\n"
        ".global NativeLayerCell\n.thumb_set NativeLayerCell,0x0808b8e5\n"
        ".global WriteNativeTilePairs\n.thumb_set WriteNativeTilePairs,0x0808b7c1\n"
        ".global CopyNativeHalfwords\n.thumb_set CopyNativeHalfwords,0x0814186d\n"
        ".global ProcessNativeEncodedText\n.thumb_set ProcessNativeEncodedText,0x08015111");
void InitializeNativeDetailCaptionPanel(void) __asm__("CoreRegion_00045B04");
void InitializeNativeDetailCaptionPanel(void)
{
    register u8 *context asm("r0");
    void *resource;
    void *header;
    u8 *graphics;
    u8 *planes;
    u8 *display;
    u16 *output;
    u32 columns;
    u32 rows;
    u32 text_origin;
    u16 zero;
    u16 *zero_target;
    void *text_context;
    const u8 *caption_root;
    const u8 *caption;
    context = gNativeDetailContext;
    resource = *(void **)(context+148);
    /* Actual initialized R0 root survives the W148 load until W144. */
    asm("" : "+r"(context));
    header = *(void **)(context+144);
    graphics = gNativeMenuGraphics;
    /* Original full graphics object precedes its W24 load. */
    asm("" : "+r"(graphics));
    planes = *(u8 **)(graphics+24);
    ConfigureNativeMenuWindow(6,12,resource,header,
        planes,planes+120,planes+240,planes+360,
        7,7,15,4,7,7,15,4,15,4);
    SnapshotNativeWindowRectangle(6);
    display = gNativeMenuDisplay;
    output = *(u16 **)(display+480);
    columns = display[496];
    rows = display[497];
    DrawNativeTextFrame(output,columns,rows,0x800,columns,13,3,11);
    WriteNativeTilePairs(6,NativeLayerCell(6,1,1,1),0x24f,13,0xb000);
    zero_target = &zero;
    /* Actual store target is formed before the zero; call uses &zero afresh. */
    asm("" : "+r"(zero_target));
    *zero_target = 0;
    CopyNativeHalfwords(&zero,(void *)0x0600c9e0,0x010001e0);
    /* Fresh context after the opaque writer/fill helpers. */
    context = gNativeDetailContext;
    /* Fresh R0 definition after CpuSet; consumed before the next call. */
    asm("" : "+r"(context));
    text_context = context+0xc4c;
    text_origin = 0x0600ca20;
    /* Native R1 origin is materialized before caption root/member definitions. */
    asm("" : "+r"(text_origin));
    caption_root = gNativeCaptionResources;
    /* Original ROM root precedes the separate +172 pointer-field load. */
    asm("" : "+r"(caption_root));
    caption = *(const u8 * const *)(caption_root+172);
    ProcessNativeEncodedText(text_context,text_origin,caption,5,1);
}
