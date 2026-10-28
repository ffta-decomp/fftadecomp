#include "dma_queue.h"

/* Start one 32-bit DMA fill using a word kept on this call's stack. */
int TryStartDmaFill32(u32 value, u32 destination, u32 count)
{
    u32 source_value = value;
    /* Keep destination live while the stack-backed source is initialized. */
    u32 destination_address = destination;
    /* The register argument is truncated only when forming DMA control. */
    u16 transfer_count = count;
    const u32 low_address_limit = 0x07ffffff;
    int channel;
    int selected;

    if (destination_address > low_address_limit) {
        channel = 3;
    } else {
        channel = 0;
        if ((u32)&source_value > low_address_limit) {
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
        u32 control = (u32)transfer_count | 0x85000000;
        volatile u32 *hardware = gDmaHardwareChannels[selected];
        hardware[0] = (u32)&source_value;
        hardware[1] = destination_address;
        hardware[2] = control;
    }
    return selected;
}
