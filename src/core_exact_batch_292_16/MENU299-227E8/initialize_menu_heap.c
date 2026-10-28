typedef unsigned char u8;
typedef unsigned int u32;
extern u8 gMenuHeapStart[];
extern void *gMenuHeap;
extern void (*const ClearMenuHeapMemory)(void *,u32);
extern void *InitializeMenuHeapPool(void *,u32);
void InitializeMenuTransitionHeap(void) __asm__("CoreGlobal36_000227E8");
void InitializeMenuTransitionHeap(void)
{
    u32 base=(u32)gMenuHeapStart;
    u32 bytes;
    if(base&3) {
        base&=~3U;
        base+=4;
    }
    bytes=0x02040000U-base;
    ClearMenuHeapMemory((void *)base,bytes);
    gMenuHeap=InitializeMenuHeapPool((void *)base,bytes);
}
__asm__(".global gMenuHeapStart\n.set gMenuHeapStart,0x020159d0\n"
        ".global gMenuHeap\n.set gMenuHeap,0x0200f434\n"
        ".global ClearMenuHeapMemory\n.set ClearMenuHeapMemory,0x0836d4b8\n"
        ".global InitializeMenuHeapPool\n.thumb_set InitializeMenuHeapPool,0x080070c9\n");
