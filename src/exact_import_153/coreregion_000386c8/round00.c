#include "interfaces.h"
int CoreRegion_000386C8(u16 requested_id,int limit)
{
    int removed=0,index;
    for(index=0;index<20;++index) {
        if(gCategoryBankState.entries[index]==requested_id) {
            gCategoryBankState.entries[index]=0;
            ++removed;
            if(removed>=limit) break;
        }
    }
    return removed;
}
