typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct NativePairCopyRequest;
struct NativePairLayer {u8 unknown00[16];u8 *buffer;};
typedef void (*NativePairClearFunction)(u8 *,s32);
extern NativePairClearFunction NativePairClear;
extern u8 NativeSelectionMemory[];
extern const u8 NativePairRecordTable[];
extern const u8 *const NativePairTextCatalog[];
extern u8 *NativePairWindowState;
extern u8 NativePairWindowScratch[];
extern struct NativePairLayer NativePairWindowLayer;
extern u8 *ResolveNativePairText(u32) asm("RetailCall_080cb4e0");
extern u32 RenderNativePairText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern struct NativePairCopyRequest *TakeNativePairWindowRequest(void) asm("RetailCall_0802dfcc");
extern void QueueNativePairWindowCopy(struct NativePairCopyRequest *,u32,u32,u16) asm("RetailCall_08000adc");
extern void UpdateNativePairWindowObjects(void) asm("RetailCall_0802eb58");
void RenderSelectedNativePairRecord(void) asm("CoreFrontier_0002F100");
void RenderSelectedNativePairRecord(void)
{
    register const u8 *selection_base asm("r1")=NativeSelectionMemory;
    u8 *initial_state;
    u8 *queue_state;
    register struct NativePairLayer *queue_layer asm("r3");
    const u8 *record;
    u8 *buffer;
    u8 selector;
    s32 selection_offset;
    register const u8 *selection_byte asm("r0");
    struct NativePairCopyRequest *request;
    u8 *destination;
    asm("" : "+r"(selection_base));
    initial_state=NativePairWindowState;
    selection_offset=2*(s32)*(s16 *)(initial_state+12);
    selection_base += 0x1F3C;
    asm("" : "+r"(selection_base));
    selection_byte=(const u8 *)((u32)selection_offset+(u32)selection_base);
    asm("" : "+r"(selection_byte));
    record=NativePairRecordTable+16*(*selection_byte);
    buffer=NativePairWindowScratch+704*(initial_state[7]+initial_state[8]);
    selector=record[1];
    NativePairClear(buffer,704);
    if (selector!=0) {
        const u8 *text=ResolveNativePairText(selector);
        RenderNativePairText(NativePairWindowState+16,(u32)buffer,text,0,1);
    } else {
        RenderNativePairText(NativePairWindowState+16,(u32)buffer,NativePairTextCatalog[0],0,1);
    }
    request=TakeNativePairWindowRequest();
    queue_layer=&NativePairWindowLayer;
    asm("" : "+r"(queue_layer));
    queue_state=NativePairWindowState;
    destination=queue_layer->buffer+8640+704*(queue_state[7]+queue_state[8]);
    QueueNativePairWindowCopy(request,(u32)buffer,(u32)destination,176);
    UpdateNativePairWindowObjects();
}
__asm__(".global NativeSelectionMemory\n.set NativeSelectionMemory,0x02000000\n"
        ".global NativePairWindowState\n.set NativePairWindowState,0x0200f444\n"
        ".global NativePairRecordTable\n.set NativePairRecordTable,0x08528f34\n"
        ".global NativePairWindowScratch\n.set NativePairWindowScratch,0x02004270\n"
        ".global NativePairClear\n.set NativePairClear,0x0836d4b8\n"
        ".global NativePairTextCatalog\n.set NativePairTextCatalog,0x085567f0\n"
        ".global NativePairWindowLayer\n.set NativePairWindowLayer,0x030008b0\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
        ".global RetailCall_080cb4e0\n.thumb_set RetailCall_080cb4e0,0x080cb4e1\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_0802dfcc\n.thumb_set RetailCall_0802dfcc,0x0802dfcd\n"
        ".global RetailCall_08000adc\n.thumb_set RetailCall_08000adc,0x08000add\n"
        ".global RetailCall_0802eb58\n.thumb_set RetailCall_0802eb58,0x0802eb59\n");
