#include "dma_queue.h"

/* Poll the DMA control register until the hardware clears its enable bit. */
void WaitForDmaChannelIdle(u32 channel)
{
    volatile u32 *hardware = gDmaWaitHardwareChannels[channel];
    while ((hardware[2] & 0x80000000) != 0) {
    }
}

/* Preserve the retail zero-filled halfword before the next function. */
__asm__(".align 2, 0");

/* Clear the DMA enable/control word through the hardware pointer table. */
void DisableDmaChannel(u32 channel)
{
    volatile u32 *hardware = gDmaWaitHardwareChannels[channel];
    hardware[2] = 0;
}
