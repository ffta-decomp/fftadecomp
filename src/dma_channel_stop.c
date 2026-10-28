#include "dma_queue.h"

extern void WaitForDmaChannelIdle(u32 channel);

/* Disable completed DMA slots, then wait until each channel is idle. */
void StopCompletedDmaChannels(void)
{
    struct DmaChannelState *active = gDmaActiveChannels;
    int channel = 0;
    u16 *busy = gDmaChannelBusy;
    volatile u32 * const *hardware = gDmaHardwareChannels;

    for (; channel <= 3; busy++, hardware++, channel++, active++) {
        if (*busy == 0 && active->state == 3) {
            (*hardware)[2] = 0;
            WaitForDmaChannelIdle(channel);
        }
    }
}
