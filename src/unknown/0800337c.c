typedef unsigned short u16;
typedef unsigned int u32;

extern void ResetOamAndAffineMatrices(void);

#if defined(DISPLAY_CONTROL_DEFAULTS)
/* Keep the IWRAM mirror and hardware display control in sync. */
void InitializeDisplayControlDefaults(void)
{
    *(u16 *)0x05000000 = 0;
    {
        u16 *display_mirror = (u16 *)0x03000940;
        u16 display_control = 0x0140;
        *display_mirror = display_control;
        *(u16 *)0x04000000 = display_control;
    }
}
#elif defined(CLEAR_VIDEO_MEMORY)
typedef struct {
    volatile u32 source;
    volatile u32 destination;
    volatile u32 control;
} DmaChannelRegisters;

/* DMA3 fills VRAM and palette RAM with zero around the OAM reset. */
void ClearVideoMemoryAndOam(void)
{
    volatile u16 zero = 0;
    volatile DmaChannelRegisters *dma3 =
        (volatile DmaChannelRegisters *)0x040000d4;
    dma3->source = (u32)&zero;
    dma3->destination = 0x06000000;
    dma3->control = 0x8100c000;
    /* Preserve the retail control-register read before touching OAM. */
    (void)dma3->control;
    ResetOamAndAffineMatrices();
    zero = 0;
    dma3->source = (u32)&zero;
    dma3->destination = 0x05000000;
    dma3->control = 0x81000200;
    (void)dma3->control;
}
#else
#error Select one display startup function
#endif
