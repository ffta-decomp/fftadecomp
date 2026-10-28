#include "dma_queue.h"

/* Start one 16-bit DMA fill using a halfword kept on this call's stack. */
int TryStartDmaFill16(u16 value, u32 destination, u32 count)
{
    u16 source_value = value;
    /* The register argument is truncated only when forming DMA control. */
    u16 transfer_count = count;
    const u32 low_address_limit = 0x07ffffff;
    int channel;
    int selected;

    if (destination > low_address_limit) {
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
        u32 control = (u32)transfer_count | 0x81000000;
        volatile u32 *hardware = gDmaHardwareChannels[selected];
        hardware[0] = (u32)&source_value;
        hardware[1] = destination;
        hardware[2] = control;
    }
    return selected;
}
