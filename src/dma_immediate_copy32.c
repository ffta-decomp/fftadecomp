#include "dma_queue.h"

/* Program one immediate 32-bit DMA transfer on a usable channel. */
int TryStartDmaCopy32(u32 source, u32 destination, u16 count)
{
    const u32 low_address_limit = 0x07ffffff;
    int channel;
    int selected;

    if (destination > low_address_limit) {
        channel = 3;
    } else {
        channel = 0;
        if (source > low_address_limit) {
            channel = 1;
        }
    }

    for (; channel <= 3; channel++) {
        if (gDmaChannelBusy[channel] == 0 &&
            (gDmaPendingChannels[channel].state == 0 ||
             gDmaPendingChannels[channel].state == 2)) {
            selected = channel;
            goto channel_selected;
        }
    }

    selected = -1;
channel_selected:
    if (selected >= 0) {
        u32 control = (u32)count | 0x84000000;
        volatile u32 *hardware = gDmaHardwareChannels[selected];
        hardware[0] = source;
        hardware[1] = destination;
        hardware[2] = control;
    }
    return selected;
}
