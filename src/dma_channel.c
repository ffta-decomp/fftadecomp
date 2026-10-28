#include "dma_queue.h"

/* Populate the pending shadow only when the channel's busy slot is clear. */
void StageDmaChannelTransfer(u32 channel, u32 source, u32 destination,
                             u32 control)
{
    if (gDmaChannelBusy[channel] == 0) {
        u32 dma_control = control | 0xa2000000;
        gDmaPendingChannels[channel].source = source;
        gDmaPendingChannels[channel].destination = destination;
        gDmaPendingChannels[channel].control = dma_control;
        gDmaPendingChannels[channel].state = 1;
        gDmaPendingChannels[channel].flags = 0x80;
    }
}

/* Mark a pending channel for cancellation when its active slot is occupied. */
void CancelDmaChannel(u32 channel)
{
    if (gDmaActiveChannels[channel].state != 0) {
        gDmaPendingChannels[channel].state = 2;
        gDmaPendingChannels[channel].flags |= 0x80;
    }
}
