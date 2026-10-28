#include "dma_queue.h"

/* Each variant keeps its queue append in place to match the retail call layout. */

/* Queue one immediate 16-bit DMA transfer descriptor. */
void QueueDmaCopy16(struct DmaRequest *request, u32 source, u32 destination,
                    u16 count)
{
    request->state = 0;
    request->flags = 1;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x80000000;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue one immediate 32-bit DMA transfer descriptor. */
void QueueDmaCopy32(struct DmaRequest *request, u32 source, u32 destination,
                    u16 count)
{
    request->state = 0;
    request->flags = 1;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x84000000;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue a 16-bit transfer with the DMA source-address mode set to fixed. */
void QueueDmaFixedSource16(struct DmaRequest *request, u16 source,
                           u32 destination, u16 count)
{
    request->state = 0;
    request->flags = 3;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x81000000;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue a 32-bit transfer with the DMA source-address mode set to fixed. */
void QueueDmaFixedSource32(struct DmaRequest *request, u32 source,
                           u32 destination, u16 count)
{
    request->state = 0;
    request->flags = 3;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x85000000;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue a sequence of 16-bit transfers with source and destination strides. */
void QueueDmaSequence16(struct DmaRequest *request, u32 source, u32 destination,
                        u16 count, u16 remaining, u16 source_stride,
                        u16 destination_stride)
{
    request->state = 1;
    request->flags = 1;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x80000000;
    request->remaining = remaining;
    request->source_stride = source_stride;
    request->destination_stride = destination_stride;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue a sequence of 32-bit transfers with source and destination strides. */
void QueueDmaSequence32(struct DmaRequest *request, u32 source, u32 destination,
                        u16 count, u16 remaining, u16 source_stride,
                        u16 destination_stride)
{
    request->state = 1;
    request->flags = 1;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x84000000;
    request->remaining = remaining;
    request->source_stride = source_stride;
    request->destination_stride = destination_stride;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue a repeated 16-bit transfer with a fixed source address. */
void QueueDmaFixedSequence16(struct DmaRequest *request, u16 source,
                             u32 destination, u16 count, u16 remaining,
                             u16 destination_stride)
{
    request->state = 1;
    request->flags = 3;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x81000000;
    request->remaining = remaining;
    request->source_stride = 0;
    request->destination_stride = destination_stride;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}

/* Queue a repeated 32-bit transfer with a fixed source address. */
void QueueDmaFixedSequence32(struct DmaRequest *request, u32 source,
                             u32 destination, u16 count, u16 remaining,
                             u16 destination_stride)
{
    request->state = 1;
    request->flags = 3;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x85000000;
    request->remaining = remaining;
    request->source_stride = 0;
    request->destination_stride = destination_stride;
    request->next = 0;

    if (gDmaQueueHead == 0) {
        gDmaQueueHead = request;
    } else {
        struct DmaRequest *tail = gDmaQueueHead;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = request;
    }
}
