#ifndef FFTA_DMA_QUEUE_H
#define FFTA_DMA_QUEUE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Layout is verified by instruction offsets; some field roles are inferred. */
struct DmaRequest {
    u8 state;
    u8 flags;
    u16 unused02;
    u32 source;
    u32 destination;
    u32 control;
    u16 remaining;
    u16 source_stride;
    u16 destination_stride;
    u16 unused16;
    struct DmaRequest *next;
};

extern struct DmaRequest *gDmaQueueHead;
extern u16 gDmaProcessMode;
extern u32 gDmaFixedSourceValue;

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

void StopCompletedDmaChannels(void);
void InitializeDmaChannels(void);
void ProcessDmaChannelShadows(void);
void ProcessDmaQueue(void);
void WaitForDmaChannelIdle(u32 channel);
void DisableDmaChannel(u32 channel);
void StageDmaChannelTransfer(u32 channel, u32 source, u32 destination,
                             u32 control);
int TryStageDmaTransfer(u32 source, u32 destination, u32 control);
void CancelDmaChannel(u32 channel);
int TryStartDmaFill32(u32 value, u32 destination, u32 count);
int TryStartDmaFill16(u16 value, u32 destination, u32 count);
int TryStartDmaCopy32(u32 source, u32 destination, u16 count);
int TryStartDmaCopy16(u32 source, u32 destination, u16 count);

void QueueDmaCopy16(struct DmaRequest *request, u32 source, u32 destination,
                    u16 count);
void QueueDmaCopy32(struct DmaRequest *request, u32 source, u32 destination,
                    u16 count);
void QueueDmaFixedSource16(struct DmaRequest *request, u16 source,
                           u32 destination, u16 count);
void QueueDmaFixedSource32(struct DmaRequest *request, u32 source,
                           u32 destination, u16 count);
void QueueDmaSequence16(struct DmaRequest *request, u32 source, u32 destination,
                        u16 count, u16 remaining, u16 source_stride,
                        u16 destination_stride);
void QueueDmaSequence32(struct DmaRequest *request, u32 source, u32 destination,
                        u16 count, u16 remaining, u16 source_stride,
                        u16 destination_stride);
void QueueDmaFixedSequence16(struct DmaRequest *request, u16 source,
                             u32 destination, u16 count, u16 remaining,
                             u16 destination_stride);
void QueueDmaFixedSequence32(struct DmaRequest *request, u32 source,
                             u32 destination, u16 count, u16 remaining,
                             u16 destination_stride);

#endif
