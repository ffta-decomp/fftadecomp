#include "dma_queue.h"

enum {
    DMA_REQUEST_MODE1_DEFER = 1,
    DMA_REQUEST_FIXED_SOURCE = 2,
    DMA_REQUEST_COMPLETE = 0x80,
    DMA_REQUEST_SEQUENCE_STATE = 1
};

/* Drain each queued request's DMA bursts, then retain deferred requests. */
void ProcessDmaQueue(void)
{
    struct DmaRequest *request = gDmaQueueHead;
    struct DmaRequest *tail;

    while (request != 0) {
        u16 *busy;
        u32 source;
        u32 loaded_source;
        u32 cartridge_limit;

        if (gDmaProcessMode == 1 &&
            (request->flags & DMA_REQUEST_MODE1_DEFER) != 0) {
            request = request->next;
            continue;
        }

        if ((request->flags & DMA_REQUEST_FIXED_SOURCE) != 0) {
            gDmaFixedSourceValue = request->source;
        }
        busy = gDmaChannelBusy;

        for (;;) {
            int channel;
            volatile u32 *hardware;

            /* A cartridge-address source or destination requires DMA 3. */
            loaded_source = request->source;
            /* Keep the retail load and live source copy distinct for agbcc. */
            __asm__ volatile ("" : "+r" (loaded_source));
            cartridge_limit = 0x07ffffff;
            source = loaded_source;
            if (source > cartridge_limit ||
                request->destination > cartridge_limit) {
                channel = 3;
            } else {
                channel = 0;
            }
            while (channel <= 3 && busy[channel] != 0) {
                channel++;
            }
            if (channel > 3) {
                break;
            }

            hardware = gDmaHardwareChannels[channel];
            hardware[0] = (request->flags & DMA_REQUEST_FIXED_SOURCE) != 0
                              ? (u32)&gDmaFixedSourceValue : source;
            hardware[1] = request->destination;
            hardware[2] = request->control;
            WaitForDmaChannelIdle(channel);

            if (request->state != DMA_REQUEST_SEQUENCE_STATE ||
                --request->remaining == 0) {
                break;
            }
            if ((request->flags & DMA_REQUEST_FIXED_SOURCE) == 0) {
                request->source += request->source_stride;
            }
            request->destination += request->destination_stride;
        }

        request->flags |= DMA_REQUEST_COMPLETE;
        request = request->next;
    }

    /* Relink live nodes; the retail routine does not clear the final next link. */
    request = gDmaQueueHead;
    tail = 0;
    gDmaQueueHead = tail;
    while (request != 0) {
        if ((request->flags & DMA_REQUEST_COMPLETE) == 0) {
            if (tail == 0) {
                tail = request;
                gDmaQueueHead = request;
            } else {
                tail->next = request;
                tail = request;
            }
        }
        request = request->next;
    }
}
