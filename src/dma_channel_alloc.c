#include "dma_queue.h"

/* Find a channel permitted for these addresses and stage its register shadow. */
int TryStageDmaTransfer(u32 source, u32 destination, u32 control)
{
    /* The cartridge ROM mapping begins at the next address, 0x08000000. */
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
            /* Skip the no-channel sentinel once a usable slot is found. */
            goto channel_selected;
        }
    }

    selected = -1;
channel_selected:
    if (selected >= 0 && gDmaChannelBusy[selected] == 0) {
        u32 dma_control = control | 0xa2000000;
        gDmaPendingChannels[selected].source = source;
        gDmaPendingChannels[selected].destination = destination;
        gDmaPendingChannels[selected].control = dma_control;
        gDmaPendingChannels[selected].state = 1;
        gDmaPendingChannels[selected].flags = 0x80;
    }
    return selected;
}
