typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct OverlayWindowDescriptor { u8 x,y,columns,rows; u16 unknown04,selector; u8 advance; u8 unknown09[7]; };
struct WindowLayerPrefix { u8 unknown00[20]; u32 buffer; };
typedef void (*ByteCopyRoutine)(u8 *,const u8 *,s32);
extern u8 *OverlayMenuRoot;
extern const ByteCopyRoutine OverlayByteCopy;
extern const u8 OverlayWindowTemplate[];
extern struct WindowLayerPrefix OverlayLayerA,OverlayLayerB;
extern u16 UpdateOverlayDescriptor(struct OverlayWindowDescriptor *);
extern void ConfigureOverlayWindow(u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void BindOverlayDescriptor(struct OverlayWindowDescriptor *,u8 *,u8 *);
extern void AdvanceOverlayWindow(u8 *,u32);
extern u8 ReadOverlayWindowReadiness(void);
extern u32 RegisterOverlayCallback(u8 (*)(void),u32);
__asm__(".global OverlayMenuRoot\n.set OverlayMenuRoot,0x0201f54c\n"
        ".global OverlayByteCopy\n.set OverlayByteCopy,0x0836d4bc\n"
        ".global OverlayWindowTemplate\n.set OverlayWindowTemplate,0x08393718\n"
        ".global OverlayLayerA\n.set OverlayLayerA,0x03000990\n"
        ".global OverlayLayerB\n.set OverlayLayerB,0x030008b0\n"
        ".global UpdateOverlayDescriptor\n.thumb_set UpdateOverlayDescriptor,0x08013b51\n"
        ".global ConfigureOverlayWindow\n.thumb_set ConfigureOverlayWindow,0x08017425\n"
        ".global BindOverlayDescriptor\n.thumb_set BindOverlayDescriptor,0x08013b7d\n"
        ".global AdvanceOverlayWindow\n.thumb_set AdvanceOverlayWindow,0x08016c91\n"
        ".global ReadOverlayWindowReadiness\n.thumb_set ReadOverlayWindowReadiness,0x0804ed45\n"
        ".global RegisterOverlayCallback\n.thumb_set RegisterOverlayCallback,0x080098f5\n"
        ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
void InitializeMenuOverlayWindow(void) __asm__("CoreRegion_0004EBD0");
void InitializeMenuOverlayWindow(void)
{
    u8 *root = OverlayMenuRoot;
    u8 *window = root+592;
    struct OverlayWindowDescriptor *descriptor = (struct OverlayWindowDescriptor *)(root+636);
    u32 callback_slot;
    OverlayByteCopy((u8 *)descriptor,OverlayWindowTemplate,16);
    UpdateOverlayDescriptor(descriptor);
    ConfigureOverlayWindow(window,OverlayLayerA.buffer,OverlayLayerB.buffer,
        descriptor->x,descriptor->y,descriptor->columns,descriptor->rows,
        descriptor->selector,32,5,1,12);
    BindOverlayDescriptor(descriptor,window,OverlayMenuRoot+1308);
    {
        u32 old_flags = window[28];
        register u32 enable_mask __asm__("r0") = 1;
        __asm__("" : "+r"(enable_mask));
        enable_mask |= old_flags;
        __asm__("" : "+r"(enable_mask));
        window[28] = (u8)enable_mask;
    }
    AdvanceOverlayWindow(window,descriptor->advance);
    callback_slot = RegisterOverlayCallback(ReadOverlayWindowReadiness,(u32)OverlayMenuRoot);
    OverlayMenuRoot[0] = (u8)callback_slot;
}
