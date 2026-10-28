#include "interfaces.h"
u8 CompleteTransitionCleanup(void) __asm__("CoreGlobal36_00024108");
u8 CompleteTransitionCleanup(void)
{
    ReleaseTransitionAllocation(&gTransitionCleanup.allocation);
    ReleaseTransitionResources();
    FinishTransitionCallbacks();
    ReleaseTransitionHeap();
    gTransitionIwram.control &= 254;
    if (gTransitionCleanup.mode == 3) {
        EnterTransitionResetLoop();
    } else {
        gTransitionPaletteControl = 0;
        *(volatile u16 *)0x05000000 = 0;
        if ((u8)IsTransitionDisplayActive())
            ClearTransitionDisplayWithFlag(3);
        else if (GetTransitionGameFlag(68))
            SetTransitionDisplayValue(9);
        else
            SetTransitionDisplayValueHighBit(1);
    }
    if (gTransitionSave.pending_flags & 8) {
        CompactDeferredUnitRoster();
        gTransitionSave.pending_flags &= ~8u;
    }
    /* This halfword aliases the mode tested above, after native cleanup. */
    gTransitionTransient.mode = 0;
    return 1;
}
