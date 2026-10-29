/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147A44.c
 * Original SHA-256: dba5925e726ff8e4340a8eb473552dc410f166fa313cb16c57cdd4f08e5f4eae
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08147A44;

extern DmaRegisters08147A44 data_040000B0;
extern u8 data_03003860[];

/* Complete [0x08147A44, 0x08147A7C): 56 bytes, 21 instructions. */
void func_08147A44(void)
{
    /* plausible: DMA0 MMIO requires word writes, control readback and completion polling. */
    volatile DmaRegisters08147A44 *dma = &data_040000B0;

    dma->source = data_03003860;
    dma->destination = (void *)0x05000000;
    dma->control = 0x84000100;
    (void)dma->control;
    while (dma->control & 0x80000000)
        ;
}
