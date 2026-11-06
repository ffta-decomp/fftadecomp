/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080023EC.c
 * Original SHA-256: f93ae07e7fc3fd8da397fabeddb7669593a4961ac0f569d59effc04acb136c3f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u32 *data;
    u16 size;
    u16 end_word;
    const void *source;
} TransferEntry080023EC;

typedef struct {
    TransferEntry080023EC entries[4];
    u32 data[0];
} TransferBuffer080023EC;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters080023EC;

extern DmaRegisters080023EC data_040000D4;

u32 *func_080023EC(TransferBuffer080023EC *buffer, u32 index,
                   const void *source, u16 size)
{
    if (index == 0) {
        /* plausible: DMA3 MMIO requires volatile writes and control readback. */
        volatile DmaRegisters080023EC *dma = &data_040000D4;
        dma->source = source;
        dma->destination = buffer->data;
        dma->control = (size >> 1) | 0x80000000;
        (void)dma->control;
        buffer->entries[0].data = buffer->data;
        buffer->entries[0].end_word = size >> 2;
    } else {
        /* plausible: DMA3 MMIO requires volatile writes and control readback. */
        volatile DmaRegisters080023EC *dma = &data_040000D4;
        dma->source = source;
        dma->destination = &buffer->data[buffer->entries[index - 1].end_word];
        dma->control = (size >> 1) | 0x80000000;
        (void)dma->control;
        buffer->entries[index].data = &buffer->data[buffer->entries[index - 1].end_word];
        buffer->entries[index].end_word = buffer->entries[index - 1].end_word + (size >> 2);
    }
    buffer->entries[index].size = size;
    buffer->entries[index].source = source;
    return buffer->entries[index].data;
}
