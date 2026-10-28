#include "interfaces.h"
/* Commit only slots explicitly selected by the offer controller. */
void CoreClosure31_00051048(void)
{
    u8 slot = 0;
    do {
        if (gOfferContext->selected[slot] == 1)
            gOfferStock[slot] = 0;
        slot++;
    } while (slot <= 19);
}
