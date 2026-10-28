#include "interfaces.h"
/* Advance the observed progression counters, refresh policy, then the packed cycle. */
void CoreRegion_000360F8(void)
{
    if (gProgressionData.inner_counter<=19) ++gProgressionData.inner_counter;
    else {
        gProgressionData.inner_counter=1;
        if(gProgressionData.outer_counter<=4) ++gProgressionData.outer_counter;
        else gProgressionData.outer_counter=1;
    }
    NRefresh();
    if (gProgressionData.flags.cycle>2) {
        gProgressionData.flags.cycle=0;
        NWrap();
    } else ++gProgressionData.flags.cycle;
}
