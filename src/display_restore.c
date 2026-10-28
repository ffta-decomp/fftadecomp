#include "display.h"

/* Restore the display and interrupt register shadows after frame work. */
void RestoreDisplayRegisters(void)
{
    *(volatile u16 *)0x04000004 = gInterruptState.display_status;
    gInterruptEnable = gInterruptState.enabled;
    *(volatile u16 *)0x04000200 = gInterruptEnable;
    *(volatile u16 *)0x04000000 = gSavedDisplayControl;
}
