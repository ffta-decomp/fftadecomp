typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct NativeDefaultRowRequest;
struct NativeDefaultRowLayer {u8 unknown00[16];u8 *buffer;};
typedef void (*NativeDefaultRowClearFunction)(u8 *,s32);
extern NativeDefaultRowClearFunction NativeDefaultRowClear;
extern const u8 *const NativeDefaultRowCatalog[];
extern u8 *NativeDefaultRowState;
extern u8 NativeDefaultRowScratch[];
extern struct NativeDefaultRowLayer NativeDefaultRowLayer;
extern u32 RenderNativeDefaultRowText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern struct NativeDefaultRowRequest *TakeNativeDefaultRowRequest(void) asm("RetailCall_0802dfcc");
extern void QueueNativeDefaultRowCopy(struct NativeDefaultRowRequest *,u32,u32,u16) asm("RetailCall_08000adc");
void RenderNativeDefaultWindowRow(void) asm("CoreFrontier_0002F1D0");
void RenderNativeDefaultWindowRow(void)
{
    u8 *initial_state=NativeDefaultRowState;
    u8 *queue_state;
    u8 *buffer=NativeDefaultRowScratch+704*(initial_state[7]+initial_state[8]);
    struct NativeDefaultRowRequest *request;
    register struct NativeDefaultRowLayer *queue_layer asm("r3");
    u8 *destination;
    NativeDefaultRowClear(buffer,704);
    RenderNativeDefaultRowText(NativeDefaultRowState+16,(u32)buffer,NativeDefaultRowCatalog[0],0,1);
    request=TakeNativeDefaultRowRequest();
    queue_layer=&NativeDefaultRowLayer;
    asm("" : "+r"(queue_layer));
    queue_state=NativeDefaultRowState;
    destination=queue_layer->buffer+8640+704*(queue_state[7]+queue_state[8]);
    QueueNativeDefaultRowCopy(request,(u32)buffer,(u32)destination,176);
}
__asm__(".global NativeDefaultRowState\n.set NativeDefaultRowState,0x0200f444\n"
        ".global NativeDefaultRowScratch\n.set NativeDefaultRowScratch,0x02004270\n"
        ".global NativeDefaultRowClear\n.set NativeDefaultRowClear,0x0836d4b8\n"
        ".global NativeDefaultRowCatalog\n.set NativeDefaultRowCatalog,0x085567f0\n"
        ".global NativeDefaultRowLayer\n.set NativeDefaultRowLayer,0x030008b0\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_0802dfcc\n.thumb_set RetailCall_0802dfcc,0x0802dfcd\n"
        ".global RetailCall_08000adc\n.thumb_set RetailCall_08000adc,0x08000add\n");
