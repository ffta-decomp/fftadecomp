typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*BufferCallback)(void *, u32);
extern void CpuFastSet(const u32 *, void *, u32);
extern void CallBufferCallback(void *, u32, BufferCallback);
__asm__(".global CpuFastSet\n.thumb_set CpuFastSet, 0x08141869\n.global CallBufferCallback\n.thumb_set CallBufferCallback, 0x0814224D");
void CoreFrontier_0001D938(void)
{
    register BufferCallback *callback_cell __asm__("r2");
    u8 *state = (u8 *)0x02008168;
    u32 fill = *(u16 *)(state + 8);
    CpuFastSet(&fill, *(void **)(state + 16), 0x01001000);
    callback_cell = (BufferCallback *)0x0836D4B8;
    /* Preserve native callback-address lifetime before constructing arguments. */
    __asm__("" : "+r"(callback_cell));
    CallBufferCallback(state + 40, 512, *callback_cell);
    state -= 552;
    {
        register u32 previous __asm__("r1") = *(u16 *)(state + 44);
        register u32 mask __asm__("r0") = 2;
        /* Defined values retain native halfword/mask register lifetimes. */
        __asm__("" : "+r"(previous), "+r"(mask));
        *(u16 *)(state + 44) = mask | previous;
    }
}
