#include "interfaces.h"
int CoreRegion_00038694(u16 requested_id)
{
    int index;
    for(index=0;index<20;++index) {
        if(gCategoryBankState.entries[index]==requested_id) {
            gCategoryBankState.entries[index]=0;
            return 1;
        }
    }
    return 0;
}
