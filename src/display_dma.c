#include "display.h"

typedef unsigned int u32;

/* Copy the display shadow block with DMA3, then restore DISPCNT. */
void ApplyDisplayRegistersDma(void)
{
    u32 source = 0x03000942;
    volatile u32 *dma = (volatile u32 *)0x040000b0;
    dma[0] = source;
    dma[1] = 0x04000008;
    dma[2] = 0x80000027;
    dma[2];
    /* Preserve agbcc's retail register allocation for the pointer reload. */
    __asm__ volatile ("" ::: "r2");
    dma = (volatile u32 *)0x040000b0;
    while (dma[2] & 0x80000000) {
    }
    gSavedDisplayControl = *(volatile u16 *)0x03000940;
}
