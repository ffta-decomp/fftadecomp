/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002480.c
 * Original SHA-256: 680770adba31ab96da1203333f924915a16c055b0aa9c588a7cee49ebad0ab1f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08002480..0x08002524: 164 bytes. */
typedef struct {
    u32 *data;
    u16 size;
    u16 end_word;
    const void *source;
} TransferEntry08002480;

typedef struct {
    TransferEntry08002480 entries[4];
    u32 data[0];
} TransferBuffer08002480;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08002480;

extern DmaRegisters08002480 data_040000D4;

void *func_08002480(TransferBuffer08002480 *buffer, u32 index,
                    const void *source, u16 size)
{
    if (index == 0) {
        /* plausible: DMA3 MMIO requires volatile writes and control readback. */
        volatile DmaRegisters08002480 *dma = &data_040000D4;
        dma->source = source;
        dma->destination = buffer->data;
        dma->control = (size >> 1) | 0x80000000;
        (void)dma->control;
        buffer->entries[0].data = buffer->data;
        buffer->entries[0].end_word = size >> 2;
    } else {
        /* plausible: DMA3 MMIO requires volatile writes and control readback. */
        volatile DmaRegisters08002480 *dma = &data_040000D4;
        dma->source = source;
        dma->destination = &buffer->data[buffer->entries[index - 1].end_word];
        dma->control = (size >> 1) | 0x80000000;
        (void)dma->control;
        buffer->entries[index].data = &buffer->data[buffer->entries[index - 1].end_word];
        buffer->entries[index].end_word = buffer->entries[index - 1].end_word + (size >> 2);
    }
    if (buffer->entries[index].end_word & 1)
        buffer->entries[index].end_word++;
    buffer->entries[index].size = size;
    buffer->entries[index].source = source;
    return buffer->entries[index].data;
}
