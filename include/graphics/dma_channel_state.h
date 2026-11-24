#ifndef FFTA_DMA_CHANNEL_STATE_H
#define FFTA_DMA_CHANNEL_STATE_H

#include "ffta/unsigned_types.h"

/* Software shadow of one DMA channel's source, destination, and control. */
struct DmaChannelState {
    u32 source;
    u32 destination;
    u32 control;
    u8 state;
    u8 flags;
    u16 unused0e;
};

extern struct DmaChannelState gDmaActiveChannels[4];
extern struct DmaChannelState gDmaPendingChannels[4];
extern u16 gDmaChannelBusy[4];
extern volatile u32 * const gDmaHardwareChannels[4];
extern volatile u32 * const gDmaWaitHardwareChannels[4];

#endif
