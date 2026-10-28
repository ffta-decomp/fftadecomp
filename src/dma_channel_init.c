#include "dma_queue.h"

extern const u32 gDmaRamInitRoutineAddress;
extern void CallR2Trampoline(void *destination, u32 size, u32 target);

/* Reset queue state and both four-channel shadows during DMA setup. */
void InitializeDmaChannels(void)
{
    u32 channel;
    for (channel = 0; channel <= 3; channel++) {
        gDmaChannelBusy[channel] = 0;
    }
    gDmaChannelBusy[1] = 1;
    gDmaQueueHead = 0;
    {
        /* The ROM passes a RAM routine address in r2 through a Thumb thunk. */
        const u32 *routine_address_word = &gDmaRamInitRoutineAddress;
        struct DmaChannelState *pending = gDmaPendingChannels;
        CallR2Trampoline(pending, 64, *routine_address_word);
        CallR2Trampoline(gDmaActiveChannels, 64, *routine_address_word);
    }
}
