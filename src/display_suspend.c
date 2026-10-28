#include "display.h"

/* Force blank and mask display interrupts while frame work is in progress. */
void SuspendDisplayRegisters(void)
{
    gSavedDisplayControl = *(volatile u16 *)0x04000000;
    *(volatile u16 *)0x04000000 = 0x80;
    gInterruptEnable = gInterruptState.enabled & 0xfff8;
    *(volatile u16 *)0x04000200 = gInterruptEnable;
}
